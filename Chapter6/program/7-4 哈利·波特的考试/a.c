#include <stdio.h>
#include <stdlib.h>

//顶点下标从1开始
#define MAX_N 101
//表示无穷值
#define INFINITE 10000000

//用邻接矩阵表示图
typedef struct MGraph_
{
    //邻接矩阵
    int matrix[MAX_N][MAX_N];
    //图中顶点数
    int nv;
    //图中边数
    int ne;
}MGraph;

//创建图
MGraph* CreateGraph(int nv)
{
    //动态分配图结构体内存
    MGraph *graph = (MGraph*)malloc(sizeof(MGraph));
    //设置边数为0
    graph->ne = 0;
    //设置顶点数
    graph->nv = nv;
    int i, j;
    //初始化任意两点之间都没有连通
    for(i=1; i<=graph->nv; ++i)
        for(j=1; j<=graph->nv; ++j)
            graph->matrix[i][j] = INFINITE;
    return graph;
}

//释放图内存
void FreeGraph(MGraph* graph)
{
    free(graph);
}

//向图中插入一条边，weight就是命令的长度
void InsertEdge(MGraph* graph, int v1, int v2, int weight)
{
    graph->matrix[v1][v2] = weight;
    //对称矩阵
    graph->matrix[v2][v1] = weight;
    //边数累加1
    ++graph->ne;
}

//Floyd算法，成功返回1，失败返回0
//sourceVID表示需要带的动物号，也就是该动物转换成其他任意动物的最大命令长度值最小
//maxDistance是这个动物最长命令的最小值
int Floyd(MGraph* graph, int *sourceVID, int *maxDistance)
{
    //Floyd需要两个数组：diss和path，这里不需要path
    int diss[MAX_N][MAX_N];
    int i, j, k;
    //初始化diss数组
    for(i=1; i<=graph->nv; ++i)
    {
        for(j=1; j<=graph->nv; ++j)
            diss[i][j] = graph->matrix[i][j];
    }

    //Floyd三层循环算法，k需要放在最外层，判断(i,j)路径中是否需要加入顶点k，从而使得(i,j)路径长度会变短
    for(k=1; k<=graph->nv; ++k)
    {
        for(i=1; i<=graph->nv; ++i)
        {
            for(j=1; j<=graph->nv; ++j)
            {
                //加入顶点k使得(i,j)之间的路径会变短
                if(diss[i][k]+diss[k][j]<diss[i][j])
                    diss[i][j] = diss[i][k]+diss[k][j];
            }
        }
    }

    //搜索任意一个动物到其他动物命令转换的最长最短值
    *maxDistance =  INFINITE;
    int maxLength;
    //遍历所有顶点
    for(i=1; i<=graph->nv; ++i)
    {
        //计算顶点i到其它任意一个顶点的最长距离
        maxLength = 0;
        for(j=1; j<=graph->nv; ++j)
        {
            if(j==i)
                continue;
            if(diss[i][j]>maxLength)
                maxLength = diss[i][j];
        }
        //如果该最长距离为无穷，则表示有非连通情况，返回失败
        if(maxLength==INFINITE)
            return 0;
        //如果该最大值比较小，则替换之前的顶点（动物）
        if(maxLength<*maxDistance)
        {
            *maxDistance = maxLength;
            *sourceVID = i;
        }
    }
    return 1;
}

int main()
{
    int N, M, i, v1, v2, weight;
    //读入顶点数量和边数量
    scanf("%d%d", &N, &M);
    //创建邻接矩阵图
    MGraph* graph = CreateGraph(N);
    //读入M条边，加入图
    for(i=0; i<M; ++i)
    {
        scanf("%d%d%d", &v1, &v2, &weight);
        InsertEdge(graph, v1, v2, weight);
    }
    int sourceVID, maxDistance;
    //Floyd算法
    int bSucc=  Floyd(graph, &sourceVID, &maxDistance);
    //释放邻接矩阵图
    FreeGraph(graph);
    if(!bSucc)
        printf("0\n");
    else
        printf("%d %d\n", sourceVID, maxDistance);
    return 0;
}
