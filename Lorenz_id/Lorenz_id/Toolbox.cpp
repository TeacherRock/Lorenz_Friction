#include "Toolbox.h"
#include "MotionCard.h"

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