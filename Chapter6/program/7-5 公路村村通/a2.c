#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1001
#define MAX_M 3003

//定义边的结构体
typedef struct Edge_
{
    int v1, v2;
    int weight;
}Edge;
//定义图的结构体
typedef struct Graph_
{
    int N, M;
    Edge edges[MAX_M];
}Graph;
//图用全局变量表示
Graph graph;

//并查集
int parents[MAX_N];
//查找根
int FindRoot(int v)
{
    if(parents[v]<0)
        return v;
    //路径压缩
    return parents[v] = FindRoot(parents[v]);
}
//树合并，按秩合并
void Union(int v1, int v2)
{
    int r1 = FindRoot(v1);
    int r2 = FindRoot(v2);
    if(r1==r2)
        return;
    if(parents[r1]<parents[r2])
        parents[r2] = r1;
    else
        parents[r1] = r2;
}
//并查集初始化
void Set_Init()
{
    int i;
    for(i=0; i<MAX_N; ++i)
        parents[i] = -1;
}

//快排比较函数
int CompEdge(const void* a, const void* b)
{
    Edge *aa = (Edge*)a;
    Edge *bb = (Edge*)b;
    return aa->weight - bb->weight;
}

void Kruskal()
{
    int i, edgeInsertedNum=0, v1, v2, sumWeight=0, w, r1, r2;

    //边快排
    qsort(graph.edges, graph.M, sizeof(graph.edges[0]), CompEdge);

    //并查集初始化
    Set_Init();

    //循环插入边
    for(i=0; i<graph.M; ++i)
    {
        v1 = graph.edges[i].v1;
        v2 = graph.edges[i].v2;
        w = graph.edges[i].weight;
        r1 = FindRoot(v1);
        r2 = FindRoot(v2);
        //如果v1, v2已经是同一棵树，则不能加入，否则会引入回路
        if(r1==r2)
            continue;
        //合并两棵树，也就是插入了边(v1, v2)
        Union(v1, v2);
        //累加MST的权值
        sumWeight+=w;
        //MST边数加1
        ++edgeInsertedNum;
        //如果插入的边数已经等于图中顶点数-1，则MST生成成功
        if(edgeInsertedNum==graph.N-1)
            break;
    }
    if(edgeInsertedNum==graph.N-1)
        printf("%d\n", sumWeight);
    else
        printf("-1\n");
}

int main()
{
    int i, j, v1, v2, w;
    scanf("%d%d", &graph.N, &graph.M);
    for(i=0; i<graph.M; ++i)
    {
        scanf("%d%d%d", &v1, &v2, &w);
        graph.edges[i].v1 = v1;
        graph.edges[i].v2 = v2;
        graph.edges[i].weight = w;
    }
    Kruskal();

    return 0;
}
