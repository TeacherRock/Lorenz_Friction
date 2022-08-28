#include "SaveData.h"
//可用Function
/*
1. void SaveData_CreateFile(char *path)
用途 : 建立實驗資料檔
輸入 : 位址
輸出 : 建立txt檔

2. void SaveData_Data(double a, double b, double c, double d, double e)
用途 : 寫入實驗資料檔
輸入 : 要存的檔案
輸出 : 將輸入寫入txt檔

3. void SaveData_Data(double a[])
用途 : 寫入實驗資料檔
輸入 : 要存的檔案
輸出 : 將輸入寫入txt檔

4, void SaveData_CloseFile()
用途 : 關閉檔案
輸入 : 無
輸出 : 無

*/


//================================================

FILE *SaveDataFile;

//================ 建立實驗資料檔 ================
void SaveData_CreateFile(char *path)
{

	// --- 建立txt檔 ---
	/* fopen(
			string filename,		// 檔案路徑及名字
			string mode)			// "w" Open for writing only;*/
	SaveDataFile = fopen(path, "w");

}

//================ 寫入實驗資料檔 ================

void SaveData_Data(double a, double b, double c, double d, double e)
{
	fprintf(SaveDataFile, "%f\t", a);
	fprintf(SaveDataFile, "%f\t", b);
	fprintf(SaveDataFile, "%f\t", c);
	fprintf(SaveDataFile, "%f\t", d);
	fprintf(SaveDataFile, "%f\t", e);


	fprintf(SaveDataFile, "\n");
}

//================ 寫入實驗資料檔 ================

void SaveData_Data(double a[])
{
	for (int i = 0; i < 1; i++)
	{
		fprintf(SaveDataFile, "%f\t", a[i]);
	}

	fprintf(SaveDataFile, "\n");
}

//================ 關閉實驗資料檔 ================

void SaveData_CloseFile()
{

	// --- 關閉txt檔 ---
	/* fclose(
			string filename)		// 檔案路徑及名字*/
	fclose(SaveDataFile);

}