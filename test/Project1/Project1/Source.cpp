//#include "MotionCard.h"
//#include "SaveData.h"
//#include "Setting.h"
//#include "Toolbox.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string inputfile = "command\\command.txt";
string outputfile = "record\\data.txt";


//�ŧi�ܼ�
double P; //��e��m
double V; //��e�t��
double A; //��e�[�t��
vector<double> pos; //��m�R�O
vector<double> vel; //�t�שR�O
vector<double> acc; //�[�t�שR�O


int main() {


	//Ū���ɮ�
	ifstream in;
	in.open(inputfile);
	if (in.fail()) {
		cout << "input file opening failed\n";
		system("pause");
		exit(1);
	}
	double p, v, a = 0;
	while (!in.eof()) {
		in >> p >> v >> a;
		pos.push_back(p);
		vel.push_back(v);
		acc.push_back(a);
	}
	in.close();
	for (int i = 0; i < pos.size(); i++) {
		cout << pos[i] << " " << vel[i] << " " << acc[i] << endl;
	}
	system("pause");


	return 0;
}