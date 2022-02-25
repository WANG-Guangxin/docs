#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <string>
#include<time.h>
#include<Windows.h>
using namespace std;


#define INF 32767 //���ֵ
#define MAXV 1000 //��󶥵���
static int numVex=0;
int status = 0;
typedef struct
{
	//char vexs[MAXV];//di
	int edges[MAXV][MAXV];
	int n;    // �������
    //int e;     //����
}MGraph;    //��ʾ�ڽӾ������������

MGraph * createmgraph(int n);
void writeToFile(int n,string fileName);
void readFromFile(MGraph *g, string fileName);
void dijkstra(MGraph *G,int v,int dist[],int path[]);
void floyd(MGraph *G,int FDist[][MAXV], int FPath[][MAXV]);

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"     *********************************************************************"<<endl;
	cout<<"     *                               ���·��                            *"<<endl;
	cout<<"     *********************************************************************"<<endl;
	cout<<"�����붥����:"<<endl;

	while( ++status){
	clock_t startTime, endTime;//��¼����ʱ��
	const int source=0;//Դ��
	int n=0;//������
	int DDist[MAXV],DPath[MAXV];//�Ͻ�˹����
	int FDist[MAXV][MAXV];
	int FPath[MAXV][MAXV];
	if(status>1)
	cout<<"�����붥����:"<<endl;
	cin>>n;
	MGraph * g= createmgraph(n );

	writeToFile(g->n,"Graph.txt");
	readFromFile(g,"Graph.txt");

	//Dijkstra
	cout << "\nDijkstra ���·��:" << endl;
	
	startTime = clock();
	for(int i = 0;i<1000;i++)
	{
	dijkstra(g,source,DDist,DPath);
	}
	endTime = clock();
	//cout << "startTime="<<startTime << ",endTime= " << endTime << endl;
	cout << "Dijkstra "<<"���㣺"<<g->n<<"��, ��ʱ: " << (double)(endTime - startTime)/1000<<"�룡"<< endl;
	//cout << "path is:" << endl;
	//void disDPath(MGraph *G,int dist[],int path[],int s[],int v);
	//printfDPath(DPath, DDist, end);
	startTime = clock();
		for(int i = 0;i<1000;i++)
	{
	floyd(g,FDist,FPath);
		}
	endTime = clock();
	//cout << "startTime="<<startTime << ",endTime= " << endTime << endl;
	cout << "\nFloyd    ���·��:" << endl;
	cout << "Floyd    "<<"���㣺"<<g->n<<"��, ��ʱ: " << (double)(endTime - startTime)/1000<<"�룡\n"<< endl;
	
	}
	system("pause");
	
	return 0;
}




void writeToFile(int n,string fileName)
{
	int num;
	cout << "�ļ��� :"<<fileName ;
	ofstream outF(fileName);
	cout<<endl;
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			i == j ? num = 0 : num= rand() % 100;
			outF << num << " ";
		}
		outF << endl;
	}
	outF.close();
	cout << "�������д��ɹ�!" << endl;
}


void readFromFile(MGraph *g, string fileName)
{
	ifstream inF(fileName);
	if (!inF)
	{
		cout << "Open file fail!" << endl;
	}

	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			if (!inF.eof())
			{
				inF >> g->edges[i][j];
			//	cout << g->edges[i][j] << " ";
			}
			else{
				cout << "Reading from the file finished!" << endl;
			}
		}
		//cout << endl;
	}
	inF.close();
	cout << "�ļ����ݶ�ȡ�ɹ�!" << endl;
}




MGraph * createmgraph(int n) //��������ͼ���ڽӾ���
{ 
	MGraph *g =(MGraph*)malloc(sizeof(MGraph));
;
	int i,j;
	g->n=n;//�������
	 
	
	
    for(i=0;i<g->n;i++)         //����ͼ���ڽӾ���
      for(j=0;j<g->n;j++)
          g->edges[i][j]=0;

	return g;
   
} 


void dijkstra(MGraph *G,int v,int dist[],int path[])
{

	int set[MAXV];
	int min, i, j, u;
	for (i = 0; i < G->n; ++i)
	{
		dist[i] = G->edges[v][i];
		set[i] = 0;
		if (G->edges[v][i] < INF)
			path[i] = v;
		else
			path[i] = -1;
	}
	set[v] = 1;
	path[v] = -1;
	for (i = 0; i < G->n; ++i)
	{
		min = INF;
		for (j = 0; j < G->n; ++j)
		if (set[j] == 0 && dist[j] < min)
		{
			u = j;
			min = dist[j];
		}
		set[u] = 1;
		for (j = 0; j <G->n; ++j)
		{
			if (set[j] == 0 && dist[u] + G->edges[u][j] < dist[j])
			{
				dist[j] = dist[u] + G->edges[u][j];
				path[j] = u;
			}
		}
	}
	//cout << endl << "Dijkstra complete" << endl;

}

void floyd(MGraph *G,int FDist[][MAXV], int FPath[][MAXV])
{
	int i, j, k;
	for (i = 0; i < G->n; ++i)
		for (j = 0; j <  G->n; ++j)
		{
			FDist[i][j] = G->edges[i][j];
			FPath[i][j] = -1;
		}
	for (k = 0; k <  G->n; ++k)
		for (i = 0; i < G->n; ++i)
			for (j = 0; j<G->n; ++j)
				if (FDist[i][j]>FDist[i][k] + FDist[k][j])
					{
						FDist[i][j] = FDist[i][k] + FDist[k][j];
						FPath[i][j] = k;
					}
	//cout << "Floyd complete" << endl;
}