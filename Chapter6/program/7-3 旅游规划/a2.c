#include <stdio.h>
#include <stdbool.h>

//最大顶点数 
#define MAX_N 501
#define INFINIT 10000000

//扩展的邻接矩阵图 ，加了费用的二维数组 
typedef struct Graph_
{
	//N顶点数， M边数 
	int N, M;
	int len[MAX_N][MAX_N];
	int fee[MAX_N][MAX_N];
}Graph;

//全局变量表示图 
Graph graph;

//在dis数组中查找未被收录的距离起点路径最短的顶点 
int FindMinDisVertex(int dis[], bool collected[])
{
	int i, v=-1;
	int minDis = INFINIT;
	for(i=0; i<graph.N; ++i)
	{
		//该顶点未被收录 
		if(collected[i]==false)
		{
			//距离起点更近 
			if(minDis>dis[i])
			{
				minDis = dis[i];
				v = i;
			}
		}
	}
	return v;
}

//Dijkstra算法，参数是起点和终点的顶点编号 
void Dijkstra(int S, int D)
{
	// Dijkstra算法：三个数组：dis， path和collected 
	//这里扩展了一个fee数组，用来记录到起点S的总路径的费用 
	int dis[MAX_N], path[MAX_N], fee[MAX_N], v;
	bool collected[MAX_N] = {false};
	int i, j;
	//初始化图 
	for(i=0; i<graph.N; ++i)
	{
		dis[i] = graph.len[S][i];
		fee[i] = graph.fee[S][i];
		//如果该顶点和起点S有边，则设置前向顶点为S 
		if(dis[i]<INFINIT)
			path[i] = S;
		else
			path[i] = -1;		
	}
//	dis[S] = 0;
//	fee[S] = 0;
	//S就是本身的路径 
	path[S] = S;
	//把S收录 
	collected[S] = true;
	//外层要遍历顶点次数次，每次收录一个顶点 
	for(j=0; j<graph.N; ++j)
	{
		//找到一个距离起点S路径最短的顶点，并且 该顶点V还未被收录过 
		v = FindMinDisVertex(dis, collected);
		//找不到，不连通 
		if(v==-1)
			break;
		//收录顶点v 
		collected[v] = true;
		//更新和v有边的顶点i的dis，fee数组 
		for(i=0; i<graph.N; ++i)
		{
			//如果i未被收录 
			if(!collected[i])
			{
				//并且v加入到路径后，i距离S更近了 
				if(dis[v]+graph.len[v][i]<dis[i])
				{
					//更新i的最短路径 
					dis[i] = dis[v] + graph.len[v][i];
					//更新i的费用 
					fee[i] = fee[v] + graph.fee[v][i];
					//更新i的前向顶点 
					path[i] = v;
				}
				//并且v加入到路径后，i距离S长度不变，但是费用减少了 
				else if(dis[v]+graph.len[v][i]==dis[i] && 
					fee[v] + graph.fee[v][i]<fee[i])
				{
					//更新i的费用 
					fee[i] = fee[v] + graph.fee[v][i];
					//更新i的前向顶点 
					path[i] = v;
				}
			}
		}
	}
	//打印起点到终点的最短距离和费用 
	printf("%d %d\n", dis[D], fee[D]);		
}

int main()
{
	int S, D, i, j, v1, v2, len, fee;
	scanf("%d%d%d%d", &graph.N, &graph.M, &S, &D);
	//初始化图 
	for(i=0; i<graph.N; ++i)
	{
		for(j=0; j<graph.N; ++j)
		{
			if(j==i)
			{
				graph.len[i][j] = 0;
				graph.fee[i][j] = 0;
			}
			else
			{
				graph.len[i][j] = INFINIT;
				graph.fee[i][j] = INFINIT;
			}
		}
	}
	//读入边，无向边 
	for(i=0; i<graph.M; ++i)
	{
		scanf("%d%d%d%d", &v1, &v2, &len, &fee);
		graph.len[v1][v2] = len;
		graph.len[v2][v1] = len;
		graph.fee[v1][v2] = fee;
		graph.fee[v2][v1] = fee;
	}
	Dijkstra(S, D);
} 
