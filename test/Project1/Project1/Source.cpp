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


//宣告變數
double P; //當前位置
double V; //當前速度
double A; //當前加速度
vector<double> pos; //位置命令
vector<double> vel; //速度命令
vector<double> acc; //加速度命令


int main() {


	//讀取檔案
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