// Partition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define MatrixLarge 100
int CutPoint = 0; 
int Matrix[MatrixLarge][MatrixLarge];
int CutSize = 0;
int CX[100];               //��ĺ�����
int CY[100];               //���������

//�����ʼ��
void Init()
{
	int i,j;
	for(i=0;i<MatrixLarge;i++)
		for(j=0;j<MatrixLarge;j++)
			Matrix[i][j] = 0;
	for(int i = 0; i< 100 ; i++)
	{
		CX[i] = 0;
		CX[j] = 0;
	}
}

//�����������
void CutPointSize()
{
	int i,x,y;
	srand((int) time(NULL));
	printf("����Ҫ�ָ�ĵ���:");
	scanf("%d",&CutSize);

	Matrix[0][0] = 1;
	CX[0] = 0;
	CY[0] = 0;
	if(CutSize>1)
	{
		for(i=1;i<CutSize;i++)
		{
			x = rand()%100;
			CX[i] = x;
			y = rand()%100;
			CY[i] = y;
			Matrix[x][y] = 1;
		}
	}
	
}

//�������
void PrintMatrix()
{
	int i,j;
	for (i=0;i<MatrixLarge;i++)
	{
		for (j=0;j<MatrixLarge;j++)
		{
			printf("%3d",Matrix[i][j]);
		}
		printf("\n");
	}
}
//�и�����
void Cut_Size()
{
//	printf("00000000000000000000\n");
	int CutSum = 0,AreaSum = 0;
 	int MaxArea = 0;              //��¼����и����
	int MyArea[100][100] = {0};       // �������п����и�����  
	int CutMatrix[100][100]= {0};    //���������и���
	int WorkMatrix[100][100] = {0};   //���ǵ����

	int intColor = 0;
	int MyColor[4] = {1,2,3,4};

	int i, j, k, l,  m, x1, y1,  p =0;
    int xMin, yMin, xMax,yMax;
    bool MyFlag;

//	printf("00000000000000000001\n");
	
	for(i = 0;i<MatrixLarge;i++)
	{
		for (j = 0;j<MatrixLarge;j++)
		{
			CutMatrix[i][j] = 0;
			MyArea[i][j] = 0;
			WorkMatrix[i][j] = 0;
		}
	}
//	printf("00000000000000000002\n");
	MyFlag = TRUE;
	intColor = 0;
	AreaSum = 0;
//	printf("00000000000000000003\n");
	do {
	//	printf("00000000000000000004\n");
		MaxArea = 0;
		for (i = 1;i<=CutSize;i++)
		{
			for (k = 1;k<MatrixLarge;k++)
			{
				for (j=1;j<MatrixLarge;j++)
				{
					WorkMatrix[i][j] = CutMatrix[i][j];
				}
			}
		//	printf("00000000000000000005\n");

			for (m = 1;m<=CutSize;m++)
			{//printf("00000000000000000006\n");
				if((CX[m] == CX[i] &&CY[m] == CY[i]) || 
					(CX[m]>CX[i] && CY[m]>CY[i]))
				{//printf("00000000000000000007\n");
					for (k=CY[m];k<MatrixLarge;k++)
					{
						for (j = CX[m];j<MatrixLarge;j++)
						{
							WorkMatrix[j][k] = WorkMatrix[j][k]+1;
						}
					}
				}
			}

			l = 0;
			m = MatrixLarge;
			x1 = MatrixLarge;

			for (k = CY[i];k<MatrixLarge;k++)
			{
				for (j = CX[i]; j<x1 ; j++)
				{
					if (WorkMatrix[j][k]>1)
					{//printf("00000000000000000008\n");
						l = l+1;
						if (k == CY[i])
						{//printf("00000000000000000009\n");
							MyArea[i][l] = j - CX[i];
							y1 = k;
							p = j -1;
						}
						else
						{//printf("000000000000000000010\n");
							MyArea[i][l] = (x1 - CX[i] + 1)*(k - CY[i]);
							y1 = k -1;
							p = x1;
						}
						if (MyArea[i][l] > MaxArea)
						{//printf("00000000000000000011\n");
							MaxArea = MyArea[i][l];
							xMin = CX[i];
							yMin = CY[i];
							xMax = p;
							yMax = y1;
						}

						m = j-1;
						j = x1;
						//printf("00000000000000000012\n");
					}
				}
				//printf("00000000000000000013\n");
				x1 = m;
			}
			if (WorkMatrix[CX[i]][CY[i]] == 1)
			{//printf("00000000000000000014\n");
				l = l+1;
				MyArea[i][l] = (x1 - CX[i] +1)*(k - CY[i]);   //����������ͬ�ĵ㣬�õ㱻������С�ĵ㸲
				
				if (MyArea[i][l] > MaxArea)
				{
					MaxArea = MyArea[i][l];
					xMin = CX[i];
					yMin = CY[i];
					xMax = x1;
					yMax = k -1;
				}
			}
		}

		if (MaxArea >0)
		{
			intColor = (intColor + 1)%4;
			AreaSum = AreaSum +MaxArea;
			for (k = yMin;k<=yMax;k++)
			{
				for (j = xMin;j<=xMax;j++)
				{
					CutMatrix[j][k] = 1;
				//	Matrix[k][j] = MyColor[intColor]; 
				}
			}
			MyFlag = FALSE;
		}
	} while(MyFlag == TRUE);

	CutSum = 0;
	for (k = 1;k<=MatrixLarge;k++)
	{
		for (j = 1;j<=MatrixLarge;j++)
		{
			if (CutMatrix[j][k] == 0)
			{
				CutSum = CutSum +1;
			}
		}
	}

	for (i = 0;i<MatrixLarge;i++)
	{
		for (j = 0;j<MatrixLarge;j++)
		{
			printf("%3d",WorkMatrix[i][j]);
		}
		printf("\n");
	}
	

	float f = (float)(AreaSum / 400.0);

	printf("�и�����:%4d (400)\n",(int)(400*f));	
	printf("�и��������:%.4f\n\n",f);
}

void Choice_Funciton()
 {
		printf("    **********************************************************************\n");
		printf("    ***************************  �����и����� ****************************\n");
		printf("    **********************************************************************\n");	
		CutPointSize();
		printf("�и��:\n");
		PrintMatrix();
		printf("�и����:\n");
		Cut_Size();				
		Init();	
 }


int main()
{
	int t = 1;
	while(t)
	{		
		Choice_Funciton();
		getchar();
		//system("PAUSE");
		//system("CLS");
		//t--;
	}	
	return 0;
}