#include "Toolbox.h"
#include "MotionCard.h"
//可用Funciton
/*
1. void Toolbox_LSF(double x, double(&y))
用途 : 估測速度 
輸入 : double x => 位置, double(&y) => "pass by reference"的速度(可被更改)
輸出(更改輸入值) : LSF 1/4 (估測速度)

2. void Toolbox_LSF_Initialization(double(&PosCmd))
用途 : 初始化估測速度
輸入 : double(&PosCmd) => 位置命令
輸出(更改輸入值) : 當前位置命令 ???

*/




//================= LSF 1/4 =================


void Toolbox_LSF(double x, double(&y))
{
	static double xTemp[4] = { 0.0 };


	//---------------------- 將前一個時刻的資料向前移動 ---------------------- 
	for (int j = 0; j < 3; j++)
	{
		xTemp[j] = xTemp[j + 1];
	}
		
	//---------------------- 新資料填在最後 ---------------------- 
	xTemp[3] = x;

	//---------------------- 計算速度 ---------------------- 
	y = (0.3 * xTemp[3] + 0.1 * xTemp[2] - 0.1 * xTemp[1] - 0.3 * xTemp[0]) / SamplingTime;


}

//================= LSF Initialization =================

void Toolbox_LSF_Initialization(double(&PosCmd))
{

	double Vel = { 0.0 };

	for (int i = 0; i < 4; i++) // LSF更新至少需4次
	{

		MotionCard_Encoder(PosCmd); // 機構角度(rad)
		Toolbox_LSF(PosCmd, Vel); // 機構速度(rad/s)

	}

}