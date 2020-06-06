#include <stdio.h>
#include <stdlib.h>

//图中顶点最大数，顶点下标从1开始
#define MAX_V 1002
//图中边的最大数，题目中边数目<=3*顶点数目，因此属于稀疏图，采用邻接表表示图
#define MAX_E 3006

//MST(minimal spanning tree)，这里采用Kruscal算法
//即首先对边长度进行排序，一条一条选取边加入到MST树中
//如果候选边的两个顶点都已经在同一个并查集里了，则该边不能加入MST中
//一共只需要加入n-1条边即可，n是图中的顶点数
//如果边数不到n-1,则说明图非连通，无法村村通

//定义边的结构体，为了对道路成本进行排序用
typedef struct Edge_
{
    //边的两个顶点编号（从1开始）
    int v1;
    int v2;
    //边的成本（道路成本）
    int cost;
}Edge;

//定义邻接表中顶点链表的结构体
typedef struct NeighborVer_
{
    //边中邻接的另一个顶点的编号
    int v; //neighbor vertex
    //next指针
    struct NeighborVer_ *next;
}NeighborVer;

//定义图中顶点链表的数组
typedef struct Vertex_
{
    //这里顶点没有名字，所以不需要额外的顶点信息
//    int verinfor;
    //用带头结点的链表表示
    NeighborVer *firstEdge;
}Vertex;

//定义图结构体
typedef struct LGraph_
{
    //顶点数
    int nv;
    //边数
    int ne;
    //顶点链表数组
    Vertex vertices[MAX_V];
    //边信息数组
    Edge edges[MAX_E];
}LGraph;

//创建基于邻接表的图，输入时顶点数目
LGraph *CreateGraph(int nv)
{
    //分配图的内存
    LGraph *graph = (LGraph*)malloc(sizeof(LGraph));
    //顶点链表都设置成带头结点的链表，所以需要再分配firstEdge的内存
    int i;
    //注意：下标从1开始
    for(i=1; i<=nv; ++i)
    {
        graph->vertices[i].firstEdge = (NeighborVer*)malloc(sizeof(NeighborVer));
        //一开始链表为空，即每个顶点都时孤立的
        graph->vertices[i].firstEdge->next = NULL;
    }
    //设置顶点数
    graph->nv=nv;
    //注意：初始边数为0
    graph->ne=0;
    return graph;
}

//释放邻接表图结构体内存
void FreeGraph(LGraph *g)
{
    NeighborVer *node, *tempNode;
    int i;
    //遍历每个顶点，释放链表数组中每个链表结点的内存
    for(i=1; i<=g->nv; ++i)
    {
        //遍历链表，释放所有结点的内存
        node = g->vertices[i].firstEdge;
        while(node)
        {
            tempNode  = node;
            node = node->next;
            free(tempNode);
        }
    }
    //释放图的内存
    free(g);
}

//向邻接表图中插入一条边
void InsertEdge(LGraph* g, int v1, int v2, int cost)
{
    //分配邻接链表结点的内存
    NeighborVer *neigh = (NeighborVer*)malloc(sizeof(NeighborVer));
    //设置邻接的顶点编号
    neigh->v = v2;
    //把该结点插入到该顶点的链表头
    neigh->next = g->vertices[v1].firstEdge->next;
    g->vertices[v1].firstEdge->next = neigh;
    //无向图，所以还要在v2的链表中再加v1的结点
    neigh = (NeighborVer*)malloc(sizeof(NeighborVer));
    neigh->v = v1;
    neigh->next = g->vertices[v2].firstEdge->next;
    g->vertices[v2].firstEdge->next = neigh;
    //加入边的信息到边数组，这是为了Kruscal的边排序用的数组
    g->edges[g->ne].cost = cost;
    g->edges[g->ne].v1 = v1;
    g->edges[g->ne].v2 = v2;
    //别忘记边数+1
    ++g->ne;
}

//并查集，采用按秩合并策略,因此parents初始都为-1，表示树高度为1
int parents[MAX_V];
//并查集初始化， 初始为-1表示每个顶点当前都是独立的集合，高度为1
void SetInit()
{
    int i;
    for(i=0; i<MAX_V; ++i)
        parents[i] = -1;
}
//找到顶点v所在并查集的根结点编号
int SetFindRoot(int v)
{
    //已经到达根节点了，返回根节点编号
    if(parents[v]<0)
        return v;
    //递归向上
    return SetFindRoot(parents[v]);
}

//合并v1和v2两个所在的并查集，按秩合并
void SetUnion(int v1, int v2)
{
    //找到v1所在集合的根节点编号
    int root1 = SetFindRoot(v1);
    //找到v2所在集合的根节点编号
    int root2 = SetFindRoot(v2);
    //如果两个顶点已经在同一个集合了，不需要再合并
    if(root1==root2)
        return;
    //如果root1集合的树比root2集合的树高，则将root2的树合并到root1
    if(parents[root1]<=parents[root2])
    {
        //记得更新树高度
        if(parents[root1]>parents[root2]-1)
            parents[root1] = parents[root2]-1;
        //将root2指向root1
        parents[root2] = root1;
    }
    else
    {
        //记得更新树高度
        if(parents[root2]>parents[root1]-1)
            parents[root2] = parents[root1]-1;
        //将root1指向root2
        parents[root1] = root2;
    }
}

//两个顶点是否已经在同一个集合
int SetSame(int v1, int v2)
{
    //找到根节点
    int root1 = SetFindRoot(v1);
    //找到根节点
    int root2 = SetFindRoot(v2);
    //如果根节点编号相同则已经是同一颗树
    return root1==root2;
}

//qsort的比较函数，成本小的边要排在前面
int CompareEdge(const void*a , const void*b)
{
    Edge *aa = (Edge*)a;
    Edge *bb = (Edge*)b;
    if(aa->cost<bb->cost)
        return -1;
    else if(aa->cost>bb->cost)
        return 1;
    else
        return 0;
}

//返回值： -1 表示多个连通分量，其他值表示MST的权值之和
//输入是原始邻接表图，输出是MST的邻接表图
int MST(LGraph* graph, LGraph* mst)
{
    int i, v1, v2, totalCost=0, edgeNum=0, cost;
    //对边按权值进行排序
    qsort(graph->edges, graph->ne, sizeof(Edge), CompareEdge);
    //初始化并查集
    SetInit();
    //一条一条选边，如果边的两个顶点已经在同一个并查集了，则不能加入这条边
    for(i=0; i<graph->ne; ++i)
    {
        v1 = graph->edges[i].v1;
        v2 = graph->edges[i].v2;
        cost = graph->edges[i].cost;
        //边的两个顶点已经在同一个并查集了，则不能加入这条边
        if(SetSame(v1, v2))
            continue;
        //把该边加入到MST邻接表图中
        InsertEdge(mst, v1, v2, cost);
        //合并两个集合
        SetUnion(v1, v2);
        //MST中边数加1
        ++edgeNum;
        //总成本累加
        totalCost += cost;
        //如果边数已经达到上限，则MST生成成功
        if(edgeNum==graph->nv-1)
            break;
    }
    //如果边数已经达到上限，则MST生成成功，返回总成本
    if(edgeNum==graph->nv-1)
        return totalCost;
    else //多个连通分量，所以MST不存在，返回-1
        return -1;
}

int main()
{
    int i, N, M, v1, v2, cost, totalCost;
    scanf("%d%d", &N, &M);
    //创建输入的邻接表图
    LGraph *graph = CreateGraph(N);
    //创建输出的MST邻接表图
    LGraph *mst = CreateGraph(N);
    //读入M条边，加入图中
    for(i=0; i<M; ++i)
    {
        scanf("%d%d%d", &v1, &v2, &cost);
        InsertEdge(graph, v1, v2, cost);
    }
    //计算MST
    totalCost = MST(graph, mst);
    //打印结果
    printf("%d\n", totalCost);
    //释放输入图
    FreeGraph(mst);
    //释放输出图
    FreeGraph(graph);
    return 0;
}
