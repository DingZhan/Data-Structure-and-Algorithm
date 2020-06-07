#include <stdio.h>
#include <stdlib.h>

//图中最大顶点数
#define MAX_N 501
//501进制编码
#define CODE_BASE 501
//表示正无穷，邻接矩阵中两个顶点之间没有边的值，该值必须大于MAX_N*CODE_BASE
#define INFINITE 10000000

//图采用邻接矩阵表示
typedef struct MGraph_
{
    //将长度和费用编码到matrix里面
    //编码：code = length*CODE_BASE+cost
    //解码：length = code/CODE_BASE; cost = code%CODE_BASE
    int matrix[MAX_N][MAX_N];
    //设置顶点个数
    int nv;
    //设置边的个数
    int ne;
}MGraph;

//创建邻接矩阵图
MGraph* CreateGraph(int nv)
{
    //动态分配图结构体内存
    MGraph *graph = (MGraph*)malloc(sizeof(MGraph));
    //设置顶点数
    graph->nv = nv;
    //将当前所有顶点之间都设置为正无穷，表示顶点之间暂时没有边相连
    int i, j;
    for(i=0; i<nv; ++i)
    {
        for(j=0; j<nv; ++j)
            graph->matrix[i][j] = INFINITE;
    }
    return graph;
}

//向邻接矩阵图中插入一条边
void InsertEdge(MGraph* graph, int v1, int v2, int length, int cost)
{
    //编码
    int code = length*CODE_BASE+cost;
    //将编码后的值设置到邻接矩阵中，无向图所以是对称阵
    graph->matrix[v1][v2] = code;
    graph->matrix[v2][v1] = code;
    ++graph->ne;
}
//释放图
void FreeGraph(MGraph* graph)
{
    free(graph);
}

//全局的路径长度数组（这里的长度是指编码后的值）
int dis[MAX_N][MAX_N];
//用简单的Floyd算法替代Dijkstra算法，Floyd简单
void Floyd(MGraph* graph)
{
    int i, j, k;
    //设置dis初始值，初始为邻接矩阵值，也可以用memset替换这个循环
    for(i=0; i<graph->nv; ++i)
    {
        for(j=0; j<graph->nv; ++j)
        {
            dis[i][j] = graph->matrix[i][j];
        }
    }
    //Floyd算法，如果顶点k的加入能让(i,j)之间的路径长度减小，则加入k
    for(k=0; k<graph->nv; ++k)
    {
        for(i=0; i<graph->nv; ++i)
        {
            for(j=0; j<graph->nv; ++j)
            {
                //顶点k的加入能让(i,j)之间的路径长度减小，则加入k
                if(dis[i][k]+dis[k][j]<dis[i][j])
                {
                    dis[i][j] = dis[i][k]+dis[k][j];
                    dis[j][i] = dis[i][j];
                }
            }
        }
    }
}

int main()
{
    int N, M, S, D, v1, v2, length, cost, i;

    scanf("%d%d%d%d", &N, &M, &S, &D);
    //创建图
    MGraph *graph = CreateGraph(N);
    //加入M条边
    for(i=0; i<M; ++i)
    {
        scanf("%d%d%d%d", &v1, &v2, &length, &cost);
        InsertEdge(graph, v1, v2, length, cost);
    }
    //调用Floyd算法
    Floyd(graph);
    //释放图
    FreeGraph(graph);
    //得到S和D之间的最短编码值
    int code = dis[S][D];
    //解码输出
    printf("%d %d\n", code/CODE_BASE, code%CODE_BASE);
    return 0;
}
