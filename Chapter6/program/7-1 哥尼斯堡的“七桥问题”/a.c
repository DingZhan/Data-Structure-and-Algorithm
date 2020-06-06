#include <stdio.h>

//欧拉回路问题要求
//1. 图必须是连通的，只有一个连通分量
//2. 所有顶点的度数都为偶数

//图中最大顶点数
#define MAX_N 1001

//顶点下标从1开始
//用邻接矩阵表示图
typedef struct MGraph_
{
    //char类型表示两顶点之间是否连通，节约空间
    char matrix[MAX_N][MAX_N];
    //顶点数
    int nv;
    //边数
    int ne;
}MGraph;

//创建邻接矩阵图，传入顶点数
MGraph *CreateGraph(int nv)
{
    //动态分配结构体内存，用calloc将结构体内容全部清为0
    MGraph *graph = (MGraph*)calloc(1, sizeof(MGraph));
    //设置顶点数
    graph->nv = nv;
    return graph;
}

//向图中插入边
void InsertEdge(MGraph* graph, int v1, int v2)
{
    //如果该边已经存在了，不要多次插入
    if(graph->matrix[v1][v2])
        return;
    //无向图，所以要设置好对称阵， 1表示两个顶点之间连通
    graph->matrix[v1][v2] = 1;
    graph->matrix[v2][v1] = 1;
    //边数+1
    ++graph->ne;
}

//释放邻接矩阵图
void FreeGraph(MGraph*graph)
{
    free(graph);
}

//计算图中度数为奇数的顶点个数
int GetOddDegreeVertexNum(const MGraph* graph)
{
    int i, j, degree=0, oddVerCount=0;
    //遍历所有顶点，顶点下标从1开始
    for(i=1; i<=graph->nv; ++i)
    {
        //清除当前顶点度数为0
        degree = 0;
        //遍历顶点i的所有邻接顶点，从而计算度数
        for(j=1; j<=graph->nv; ++j)
        {
            if(graph->matrix[i][j])
                ++degree;
        }
        //如果度数为奇数，则累加
        if(degree%2==1)
            ++oddVerCount;
    }
    return oddVerCount;
}

//DFS遍历连通分量
void DFS(MGraph* graph, int v, char *visited)
{
    int i;
    visited[v] = 1;
    for(i=1; i<=graph->nv; ++i)
    {
        //如果(v, i)是一条边并且顶点i未被访问过，则递归调用DFS
        if(!visited[i] && graph->matrix[v][i])
            DFS(graph, i, visited);
    }
}

//利用DFS，得到图中的连通分量的个数。欧拉回路问题要求图必须是连通的
int GetNumberofRegions(MGraph* graph)
{
    char visited[MAX_N]={0};
    int i, regionNum=0;
    for(i=1; i<=graph->nv; ++i)
    {
        if(visited[i])
            continue;
        DFS(graph, i, visited);
        ++regionNum;
    }
    return regionNum;
}

int main()
{
    int N, M, i, v1, v2;
    scanf("%d%d", &N, &M);
    //创建图
    MGraph *graph = CreateGraph(N);
    //加入M条边
    for(i=0; i<M; ++i)
    {
        scanf("%d%d", &v1, &v2);
        InsertEdge(graph, v1, v2);
    }
    //得到连通区域个数
    int regions = GetNumberofRegions(graph);
    int oddVerNum = 1;
    //欧拉回路问题要求图必须是连通的，因此只有连通图才需要进一步的顶点度数测试
    if(regions==1)
        oddVerNum = GetOddDegreeVertexNum(graph);
    printf("%d\n", oddVerNum?0:1);
    //释放图
    FreeGraph(graph);
    return 0;
}
