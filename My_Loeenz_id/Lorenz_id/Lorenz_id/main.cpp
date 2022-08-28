//#include "MotionCard.h"
//#include "SaveData.h"
//#include "Setting.h"
//#include "Toolbox.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string inputfile = "command\command.txt";
string outputfile = "record\data.txt";


//宣告變數
double P; //當前位置
double V; //當前速度
double A; //當前加速度
double PosCmd; //當前位置命令
double VelCmd; //當前速度命令
double AccCmd; //當前加速度命令
double TorCrtl; //當前控制力矩訊號
double TorCtrl_Feedback; //當前控制回授訊號
vector<double> pos; //位置命令
vector<double> vel; //速度命令
vector<double> acc; //加速度命令



int main(){
	//讀取檔案
	ifstream in;
	in.open(inputfile);
	if (in.fail()){
		cout << "input file opening failed\n";
		exit(1);
	}
	double p, v, a = 0;
	while (!in.eof()){
		in >> p >> v >> a;
		pos.push_back(p);
		vel.push_back(v);
		acc.push_back(a);
	}
	in.close();
	for (int i = 0; i < pos.size(); i++){
		cout << pos[i] << " " << vel[i] << " " << acc[i] << endl;
	}
	system("pause");


	return 0;
}

//控制器 : 設定控制訊號
void Controller_Frrdback(double P, double PosCmd, double V, double VelCmd, double AccCmd, double &TorCtrl ) {
	double Jm = 0.0;
	double Bm = 0.0;
	double fc = 0.0;
	double fs = 0.0;
	double Kp[3] = { 250, 2, 2 };
	double Kv[3] = { 0.01, 0.01, 0.01 };
	int AXIS = 1;
	int i = AXIS - 1;

	TorCtrl_Feedback = Kp[i] * (PosCmd - P) + Kv[i] * (VelCmd - V);
	TorCtrl = TorCtrl_Feedback;
}

//


