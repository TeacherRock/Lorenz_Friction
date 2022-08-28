#include "SaveData.h"
//�i��Function
/*
1. void SaveData_CreateFile(char *path)
�γ~ : �إ߹�������
��J : ��}
��X : �إ�txt��

2. void SaveData_Data(double a, double b, double c, double d, double e)
�γ~ : �g�J��������
��J : �n�s���ɮ�
��X : �N��J�g�Jtxt��

3. void SaveData_Data(double a[])
�γ~ : �g�J��������
��J : �n�s���ɮ�
��X : �N��J�g�Jtxt��

4, void SaveData_CloseFile()
�γ~ : �����ɮ�
��J : �L
��X : �L

*/


//================================================

FILE *SaveDataFile;

//================ �إ߹������� ================
void SaveData_CreateFile(char *path)
{

	// --- �إ�txt�� ---
	/* fopen(
			string filename,		// �ɮ׸��|�ΦW�r
			string mode)			// "w" Open for writing only;*/
	SaveDataFile = fopen(path, "w");

}

//================ �g�J�������� ================

void SaveData_Data(double a, double b, double c, double d, double e)
{
	fprintf(SaveDataFile, "%f\t", a);
	fprintf(SaveDataFile, "%f\t", b);
	fprintf(SaveDataFile, "%f\t", c);
	fprintf(SaveDataFile, "%f\t", d);
	fprintf(SaveDataFile, "%f\t", e);


	fprintf(SaveDataFile, "\n");
}

//================ �g�J�������� ================

void SaveData_Data(double a[])
{
	for (int i = 0; i < 1; i++)
	{
		fprintf(SaveDataFile, "%f\t", a[i]);
	}

	fprintf(SaveDataFile, "\n");
}

//================ ������������ ================

void SaveData_CloseFile()
{

	// --- ����txt�� ---
	/* fclose(
			string filename)		// �ɮ׸��|�ΦW�r*/
	fclose(SaveDataFile);

}