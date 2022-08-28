#include "Toolbox.h"
#include "MotionCard.h"
//�i��Funciton
/*
1. void Toolbox_LSF(double x, double(&y))
�γ~ : �����t�� 
��J : double x => ��m, double(&y) => "pass by reference"���t��(�i�Q���)
��X(����J��) : LSF 1/4 (�����t��)

2. void Toolbox_LSF_Initialization(double(&PosCmd))
�γ~ : ��l�Ʀ����t��
��J : double(&PosCmd) => ��m�R�O
��X(����J��) : ��e��m�R�O ???

*/




//================= LSF 1/4 =================


void Toolbox_LSF(double x, double(&y))
{
	static double xTemp[4] = { 0.0 };


	//---------------------- �N�e�@�Ӯɨ誺��ƦV�e���� ---------------------- 
	for (int j = 0; j < 3; j++)
	{
		xTemp[j] = xTemp[j + 1];
	}
		
	//---------------------- �s��ƶ�b�̫� ---------------------- 
	xTemp[3] = x;

	//---------------------- �p��t�� ---------------------- 
	y = (0.3 * xTemp[3] + 0.1 * xTemp[2] - 0.1 * xTemp[1] - 0.3 * xTemp[0]) / SamplingTime;


}

//================= LSF Initialization =================

void Toolbox_LSF_Initialization(double(&PosCmd))
{

	double Vel = { 0.0 };

	for (int i = 0; i < 4; i++) // LSF��s�ܤֻ�4��
	{

		MotionCard_Encoder(PosCmd); // ���c����(rad)
		Toolbox_LSF(PosCmd, Vel); // ���c�t��(rad/s)

	}

}