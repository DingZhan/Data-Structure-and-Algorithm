#include <stdio.h>
#include <stdlib.h>

//图中最大顶点数，顶点下标从1开始
#define MAX_N 202

//用邻接矩阵表示无向图的结构体
typedef struct MGraph_
{
    //用char表示bool类型，如果(i,j)有边，则该值为1，该数组初始化为0
    char matrix[MAX_N][MAX_N];
    //图中顶点数目
    int nv;
    //图中边数目
    int ne;
} MGraph;

//动态创建邻接矩阵图
MGraph *CreateGraph(int nv)
{
    //用calloc把结构体中所有元素初始化为0
    MGraph* graph = (MGraph*)calloc(1, sizeof(MGraph));
    //设置顶点数目
    graph->nv = nv;
    return graph;
}

//释放邻接矩阵图内存
void FreeGraph(MGraph*graph)
{
    free(graph);
}

//向图中插入一条边
void InsertEdge(MGraph* graph, int v1, int v2)
{
    graph->matrix[v1][v2] = 1;
    //无向图，所以是对称阵
    graph->matrix[v2][v1] = 1;
    //边数累加
    ++graph->ne;
}

//判断输入的路径是否是Hamilton回路，即每个顶点只访问一次，最后要回到起始点
//所以内部判断包括：该路径中的点数目是否是nv+1,每个顶点都只能被访问一次（除了起始点）
//相邻顶点之间都有一条边
int IsHamiltonLoop(MGraph *graph, int n, int *vIDs)
{
    //每个顶点都只能被访问一次（除了起始点）
    char visited[MAX_N]= {0};
    int i, lastID;
    //如果路径中顶点数不等于图中顶点数+1，则不满足所有顶点都被访问的条件
    if(n!=graph->nv+1)
        return 0;
    //是否闭合路径（回路）
    if(vIDs[0]!=vIDs[n-1])
        return 0;
    //是否有非法顶点下标
    if(vIDs[0]<=0 || vIDs[0]>graph->nv)
        return 0;
    //标记第一个顶点被访问了
    visited[vIDs[0]] = 1;
    //记录第一个顶点，后面要用(last, vIDs[i])判断图中是否有这样一条边
    lastID = vIDs[0];
    //遍历路径中所有顶点
    for(i=1; i<n; ++i)
    {
        //该顶点下标是否非法
        if(vIDs[i]<=0 || vIDs[i]>graph->nv)
            return 0;
        //除了最后一个顶点是需要二次访问的，其他所有顶点只能被访问一次
        if(i!=n-1 && visited[vIDs[i]])
            return 0;
        //(last, vIDs[i])边是否存在
        if(!graph->matrix[lastID][vIDs[i]])
            return 0;
        //设置顶点访问标记位
        visited[vIDs[i]] = 1;
        //刷新上一个顶点下标
        lastID = vIDs[i];
    }
    //是Hamilton回路
    return 1;
}
int main()
{
    int N, M, K, i, v1, v2, n, j;
    int vIDs[MAX_N];
    scanf("%d%d", &N, &M);
    //创建图结构体
    MGraph *graph = CreateGraph(N);
    //读入M条边到图中
    for(i=0; i<M; ++i)
    {
        scanf("%d%d", &v1, &v2);
        InsertEdge(graph, v1, v2);
    }
    scanf("%d", &K);
    //读入K个路径
    for(i=0; i<K; ++i)
    {
        //当前路径中的顶点数目
        scanf("%d", &n);
        //如果该顶点数目不等于nv+1,则肯定不是Hamilton回路，则吃掉该吃的顶点，然后打印NO
        if(n!=graph->nv+1)
        {
            for(j=0; j<n; ++j)
                scanf("%d", vIDs+0);
            printf("NO\n");
        }
        else
        {
            //读入n个顶点
            for(j=0; j<n; ++j)
                scanf("%d", vIDs+j);
            //是否是Hamilton回路
            if(IsHamiltonLoop(graph, n, vIDs))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    //释放图内存
    FreeGraph(graph);
    return 0;
}
