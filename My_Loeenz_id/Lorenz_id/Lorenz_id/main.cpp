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


//�ŧi�ܼ�
double P; //��e��m
double V; //��e�t��
double A; //��e�[�t��
double PosCmd; //��e��m�R�O
double VelCmd; //��e�t�שR�O
double AccCmd; //��e�[�t�שR�O
double TorCrtl; //��e����O�x�T��
double TorCtrl_Feedback; //��e����^�°T��
vector<double> pos; //��m�R�O
vector<double> vel; //�t�שR�O
vector<double> acc; //�[�t�שR�O



int main(){
	//Ū���ɮ�
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

//��� : �]�w����T��
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


