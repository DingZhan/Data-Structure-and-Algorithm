#include <stdio.h>
#include <stdlib.h>

//图中最大顶点数，顶点下标从1开始
#define MAX_N 102
//泳池半径
#define POOL_RADIUS 15

//顶点坐标
typedef struct Coord_
{
    int x;
    int y;
}Coord;

//VT_NONE，表示该顶点不是任何特征点；
//VT_CENTER，表示从中心池能跳到该顶点，
//VT_BOUND， 表示该顶点能跳到岸上；
//VT_BOTH，表示该顶点既能跳到岸上，也能从中心池跳到该顶点
typedef enum VertexTag_{VT_NONE=0, VT_BOUND, VT_CENTER, VT_BOTH}VertexTag;

//用邻接矩阵表示无向图的结构体
typedef struct MGraph_
{
    //用char表示bool类型，如果(i,j)有边，则该值为1，该数组初始化为0
    //表示任意两个顶点都太远，跳不过去
    char matrix[MAX_N][MAX_N];
    //顶点特征数组
    VertexTag vertexBoundTags[MAX_N];
    //顶点坐标
    Coord coords[MAX_N];
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

//如果两个顶点之间距离小于跨度值，则有一条边相连
//这里需要通过计算顶点之间的距离判断是否存在这样的边
void CalculateEdges(MGraph* graph, int D)
{
    int i, j;
    int dis, D2;
    D2 = D*D;
    for(i=0; i<graph->nv; ++i)
    {
        for(j=i+1; j<graph->nv; ++j)
        {
            //如果两点之间的平方距离小于给定的阈值,则存在一条边
            dis = (graph->coords[i].x-graph->coords[j].x)*(graph->coords[i].x-graph->coords[j].x)+
            (graph->coords[i].y-graph->coords[j].y)*(graph->coords[i].y-graph->coords[j].y);
            if(dis<=D2)
            {
                //(i,j)之间设置边
                graph->matrix[i][j] = 1;
                //无向图，所以需要设置对称阵
                graph->matrix[j][i] = 1;
                //边数累加
                ++graph->ne;
            }
        }
    }
}

//计算顶点属性：中心点、边界点、都是或者都不是
void CalculateVertexTag(MGraph* graph, int D)
{
    int i, centerTag, boundTag;
    //James能从中心点跳到的最大半径的平方距离
    int D2 = (POOL_RADIUS+D)*(POOL_RADIUS+D);
    for(i=0; i<graph->nv; ++i)
    {
        centerTag = 0;
        boundTag = 0;
        //中心点标记
        if((graph->coords[i].x*graph->coords[i].x+graph->coords[i].y*graph->coords[i].y)<=D2)
            centerTag = 1;
        //边界点标记
        if(abs(50-graph->coords[i].x)<=D || abs(-50-graph->coords[i].x)<=D||
           abs(50-graph->coords[i].y)<=D || abs(-50-graph->coords[i].y)<=D)
            boundTag = 1;
        //两者都是
        if(boundTag && centerTag)
            graph->vertexBoundTags[i] = VT_BOTH;
        //只是边界点
        else if(boundTag)
            graph->vertexBoundTags[i] = VT_BOUND;
        //只是中心点
        else if(centerTag)
            graph->vertexBoundTags[i] = VT_CENTER;
    }
}

//利用DFS查找从srcVer开始的中心点是否能到边界顶点，可以把找到的边界顶点设置到boundVer上
void DFSFindBound(MGraph* graph, int srcVer, char *visited, int *boundVer)
{
    //设置访问标记
    visited[srcVer] = 1;
    //如果顶点是边界点或者是Both，则找到了这样的逃生路径，boundVer是逃生的最后一个顶点
    if(graph->vertexBoundTags[srcVer]==VT_BOUND||
       graph->vertexBoundTags[srcVer]==VT_BOTH)
    {
        *boundVer = srcVer;
        return;
    }
    int i;
    //深度优先遍历
    for(i=0; i<graph->nv; ++i)
    {
        if(visited[i] || !graph->matrix[srcVer][i])
            continue;
        DFSFindBound(graph, i, visited, boundVer);
    }
    return;
}

//图中可能有多个连通集合，只需要一个能从Center到Bound的路径
int SolutionByDFS(MGraph *graph)
{
    //顶点访问标记数组
    char visited[MAX_N]= {0};
    int i, boundVer=-1;

    //访问所有连通集，直到找到一个从Center到Bound的路径
    for(i=0; i<graph->nv; ++i)
    {
        if(visited[i])
            continue;
        //找到了既是中心也是边界的顶点
        if(graph->vertexBoundTags[i]==VT_BOTH)
            return 1;
        //起点必须是中心点
        if(graph->vertexBoundTags[i]!=VT_CENTER)
            continue;
        //深度优先遍历顶点i所在的连通集
        DFSFindBound(graph, i, visited, &boundVer);
        if(boundVer!=-1)
            return 1;
    }
    return 0;
}

int main()
{
    int N, i, D;

    scanf("%d%d", &N, &D);
    //创建图结构体
    MGraph *graph = CreateGraph(N);

    //读入M条边到图中
    for(i=0; i<N; ++i)
    {
        scanf("%d%d", &graph->coords[i].x, &graph->coords[i].y);
    }
    //计算图中的边
    CalculateEdges(graph, D);
    //计算图中的顶点属性
    CalculateVertexTag(graph, D);
    //遍历连通集查找逃生路径
    if(SolutionByDFS(graph))
        printf("Yes\n");
    else
        printf("No\n");

    //释放图内存
    FreeGraph(graph);
    return 0;
}
