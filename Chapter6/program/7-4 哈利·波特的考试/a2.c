#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//最大顶点数 
#define MAX_N 101
//正无穷 
#define INFINIT 10000000

//Floyd算法图使用邻接矩阵 
typedef struct Graph_
{
	int N, M;
	int mat[MAX_N][MAX_N];
}Graph;
//使用全局图变量 
Graph graph;

//Floyd算法 
void Floyd()
{
	//Floyd算法使用两个二维数组，dis[i][j]表示<i,j>之间路径的最短距离 
	//path[i][j]表示i，j之间需要经过顶点path[i][j] 
	int path[MAX_N][MAX_N], dis[MAX_N][MAX_N];
	int i, j, k;
	//初始化path和dis数组，本题不需要path数组 
	for(i=1; i<=graph.N; ++i)
	{
		for(j=1; j<=graph.N; ++j)
		{
			dis[i][j] = graph.mat[i][j];
			//i，j路径先不需要插入任何顶点 
			path[i][j]= -1;
		}
	}
	//Floyd三层循环，k在最外层，即判断顶点k加入后，<i,j>路径是否能变短 
	for(k=1; k<=graph.N; ++k)
	{
		for(i=1; i<=graph.N; ++i)
		{
			for(j=1; j<=graph.N; ++j)
			{
				//判断顶点k加入后，<i,j>路径是否能变短 
				if(dis[i][k]+dis[k][j]<dis[i][j])
				{
					//刷新<i,j>最短距离和中间顶点 
					dis[i][j] = dis[i][k]+dis[k][j];
					path[i][j] = k;
				}
			}
		}
	}
	
	//查找最小最大距离的起始顶点 
	int minMax = INFINIT, max, candidate=-1;
	for(i=1; i<=graph.N; ++i)
	{
		//查找顶点i为起点的，到其它任意顶点的最大距离 
		max = 0;
		for(j=1; j<=graph.N; ++j)
		{
			if(i==j) 
				continue;
			if(max<dis[i][j])
				max = dis[i][j];
		}
		//如果该最大距离比最小的最大距离还小，则更新该距离 
		if(max<minMax)
		{
			minMax = max;
			candidate = i;
		}
	}
	//如果没找到这种顶点（不连通） 
	if(candidate==-1)
		printf("0");
	else
		printf("%d %d", candidate, minMax);
}

int main()
{
    int i, j, v1, v2, w;
    scanf("%d%d", &graph.N, &graph.M);
    //初始化邻接矩阵二维数组 
	for(i=1; i<=graph.N; ++i)
	{
		for(j=1; j<=graph.N; ++j)
		{
			//<i,i>设置为0 ，否则设置为正无穷 
			if(i==j)
				graph.mat[i][j] = 0;
			else
				graph.mat[i][j] = INFINIT;
		}
	}
	//读入该图 
	for(i=0; i<graph.M; ++i)
	{
		scanf("%d%d%d", &v1, &v2, &w);
		graph.mat[v1][v2] = w;
		graph.mat[v2][v1] = w;
	}
	//Floyd算法 
	Floyd();
	
    return 0;
}
