#include "MotionCard.h"
#include "Setting.h"
#include "SaveData.h"
#include "Toolbox.h"
#define INPUT_FILENAME "data\\curve.txt"
#define OUTPUT_FILENAME "data\\data_S5_0122.txt"

using namespace std;

double Pos = { 0.0 }; // 絪絏竟à
double Vel = { 0.0 }; // LSF硉
double Vol = { 0.0 };
double PosCmd = { 0.0 }; // à㏑
double VelCmd = { 0.0 }; // 硉㏑
double AccCmd = { 0.0 }; // 硉㏑
double TorCtrl = { 0.0 }; // 锣痻北癟腹
double TorCtrl_Feedback = { 0.0 };
double *pos = NULL;
double *spd = NULL;
double *acc = NULL;
int j = 0;
int TimerFlag = 0;
int StayCount = 0;
int numLine = 0;
int count_initial = 0;

FILE *C_openFile(const char *fileName, const char *mode);
void alloc_mem(int n);

//=================北竟=============//
void Control_Feedback(double Pos, double Vel, double PosCmd, double VelCmd, double AccCmd, double(&TorCtrl))
{
	double Jm = 1.6588E-04;
	double Bm = 4.8858E-04;
	double fc = 0.0244;
	double fs = 0.0290;
	double Ka[3] = { 250, 2.0, 2.0 };
	double ba[3] = { 0.01, 0.01, 0.01 };
	int i = AXIS - 1;
	TorCtrl_Feedback = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos);
	if (Vel < 0){
		fc = -fc;
		fs = -fs;
	}
	//TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos);
	//TorCtrl = ba[i] * (Ka[i] * (PosCmd - Pos) - Vel); //PD-like controller
	//TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos) + AccCmd*Jm; //干J // 锣痻北㏑(Nm)
	//TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos) + AccCmd*Jm + VelCmd*Bm; //干J B;
	//TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos) + AccCmd*Jm + VelCmd*Bm + fc;//干JB fc
	if (Vel>-0.5 || Vel < 0.5){
		TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos) + AccCmd*Jm + VelCmd*Bm + fs;//干JB fc
	}
	else{
		TorCtrl = ba[i] * (VelCmd - Vel) + Ka[i] * (PosCmd - Pos) + AccCmd*Jm + VelCmd*Bm + fc;//干JB fc
	}
	 
}
//===============北絯侥============//

void _stdcall Timer_Stay(TMRINT *pstINTSource)
{
	//----------------------- 纗弄à硉 -----------------------
	MotionCard_Encoder(Pos); // 诀篶à
	Toolbox_LSF(Pos, Vel); // 诀篶硉

	//----------------------- 北 -----------------------

	Control_Feedback(Pos, Vel, PosCmd, VelCmd, AccCmd, TorCtrl); // 甭北

	MotionCard_DAC(TorCtrl); // 癳北㏑

	//----------------------- ち传い耞 -----------------------

	if (TimerFlag == 0 && StayCount >= 1000) // 絯侥 1
	{

		TimerFlag = 1;
		cout << "---------- 絯侥1 挡 ----------" << endl;

	}
	else if (TimerFlag == 2 && StayCount >= 2000) // 絯侥 2
	{

		TimerFlag = 3;
		cout << "---------- 絯侥2 挡 ----------" << endl;

	}
	else if (TimerFlag == 4 && StayCount >= 3000) // 絯侥 3
	{

		TimerFlag = 5;
		cout << "---------- 絯侥3 挡 ----------" << endl;

	}
	else if (TimerFlag == 5 && StayCount >= 4000) // 絯侥4
	{
		TimerFlag = 6;
		cout << "---------- 絯侥4 挡 ----------" << endl;
	}
	//SaveData_Data(Pos, Vel, PosCmd, VelCmd, Vol);
	StayCount++;
}
//==============琵禸锣传FUNCTION  (筿福セō籔禸ぃ砰)=======//

void _stdcall InitialPos(TMRINT *pstINTSource){
	MotionCard_Encoder(Pos); // 诀篶à
	Toolbox_LSF(Pos, Vel); // 诀篶硉

	//----------------------- 北 -----------------------

	Control_Feedback(Pos, Vel, 0.0, 0.0, 0.0, TorCtrl); // 甭北        ////////////////////////

	MotionCard_DAC(TorCtrl); // 癳北㏑
	count_initial++;
	if (count_initial > 1000) TimerFlag = 2;
}

void _stdcall Tracking(TMRINT *pstINTSource)
{
	//---------------------- 弄à硉 ----------------------

	MotionCard_Encoder(Pos); // 诀篶à(rad)
	Toolbox_LSF(Pos, Vel); // 诀篶à硉(rad/s)

	//---------------------- PTP Control ----------------------
	PosCmd = pos[j];
	VelCmd = spd[j];
	AccCmd = acc[j];

	Control_Feedback(Pos, Vel, PosCmd, VelCmd, AccCmd, TorCtrl);

	MotionCard_DAC(TorCtrl, Vol);

	////----------------------- 纗龟喷戈 -----------------------

	if (TimerFlag == 3)
	{

		SaveData_Data(Pos, Vel, PosCmd, VelCmd, TorCtrl_Feedback);

	}
	j++;
	if (j == numLine + 1){
		TimerFlag = 4;
	}
}

int main(){
	//=================弄ㄓmatlab璸衡Ч计沮===================//
	FILE *fp = C_openFile(INPUT_FILENAME, "r");
	// Get File Line Number
	char flag;
	while (!feof(fp)){
		flag = fgetc(fp);
		if (flag == '\n')
			numLine++;
	}
	fseek(fp, 0L, SEEK_SET); // File pointer seek to top

	alloc_mem(numLine);
	for (int i = 0; i < numLine; i++)
		fscanf(fp, "%lf	%lf	%lf\n", &pos[i], &spd[i], &acc[i]);

	double inipos = pos[0];

	//=================糶诀瘪计沮===================//
	SaveData_CreateFile(OUTPUT_FILENAME);

	//=================秨币兜===================//
	printf("Press 'Esc' to end program.\n");
	printf("Press any key to start !\n");

	while (_kbhit() == 0); // ヴ種龄秨﹍祘Α
	MotionCard_OpenCard(); // 秨币禸
	Toolbox_LSF_Initialization(PosCmd); // ﹍て LSF
	MotionCard_ServoOn(); // Servo On
	//=================巨瑈祘======================//
	int sw = 0;
	while (sw != 0x1b){
		//=================ESC挡祘Α======================//
		if (_kbhit())
		{

			sw = _getch(); // ESC挡祘Α

		}

		if (TimerFlag == 0){

			MotionCard_ChangeTimer(Timer_Stay);

		}
		else if (TimerFlag == 1){

			MotionCard_ChangeTimer(InitialPos);

		}
		else if (TimerFlag == 2){

			MotionCard_ChangeTimer(Timer_Stay);

		}
		else if (TimerFlag == 3){

			MotionCard_ChangeTimer(Tracking);

		}
		else if (TimerFlag == 4){

			MotionCard_ChangeTimer(Timer_Stay);

		}
		else if (TimerFlag == 5){

			MotionCard_ChangeTimer(Timer_Stay);

		}
		else if (TimerFlag == 6){

			break;

		}
	}

	MotionCard_Serco_Off(); // Servo Off
	MotionCard_CloseCard(); // 闽超禸
	SaveData_CloseFile();
	fclose(fp);

	// Release Memory
	delete[] pos;
	delete[] spd;
	delete[] acc;
}

FILE *C_openFile(const char *fileName, const char *mode)
{
	FILE *fp = fopen(fileName, mode);
	if (fp == NULL)
	{
		fprintf(stderr, "Error while opening \"%s\".\n", fileName);
		system("pause");
		exit(EXIT_FAILURE);
	}
	return fp;
}

void alloc_mem(int n)
{
	try
	{
		pos = new double[n];
		spd = new double[n];
		acc = new double[n];
	}
	catch (bad_alloc& ba)
	{
		cerr << "bad_alloc caught: " << ba.what() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}