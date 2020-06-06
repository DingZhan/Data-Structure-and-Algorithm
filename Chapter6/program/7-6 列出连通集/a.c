#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图中顶点最大数，也是队列长度最大值
#define MAX_N 12
//错误值，例如队列为空时出队操作
#define ERROR -1
//字符串最大长度，连通图总最多有10个顶点， 10*2 + 2 = 22 理论上23个字符足够
#define MAX_STR_LEN 30

//Adjacent Matrix Graph data structure
//定义邻接矩阵结构体
typedef struct MGraph_
{
    int nv; //图顶点数
    int ne; //图边数
    //邻接矩阵，为了节省内存，用char类型表示顶点(i,j)之间是否有边相连
    char matrix[MAX_N][MAX_N];
}MGraph;

//创建邻接矩阵结构体，传入顶点数和边数
MGraph* CreateGraph(int nv, int ne)
{
    //动态分配结构体内存，用calloc初始化内容为0
    MGraph* g = (MGraph*)calloc(1, sizeof(MGraph));
    //设置顶点数
    g->nv = nv;
    //设置边数
    g->ne = ne;
    return g;
}
//释放图结构体内存
void FreeGraph(MGraph* g)
{
    free(g);
}
//向图中插入一条边
void InsertEdge(MGraph* g, int v1, int v2)
{
    //无向图，所以需要同时设置(v1,v2)和(v2, v1)
    g->matrix[v1][v2] = 1;
    g->matrix[v2][v1] = 1;
}

//stack data structure
//堆栈结构体及相关API，这里DFS我们用递归方法实现，所以用不着Stack结构体及相关函数了
typedef struct Stack_
{
    int data[MAX_N];
    int top;
}Stack;
Stack* CreateStack()
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}
void FreeStack(Stack*s)
{
    free(s);
}
int IsStackEmpty(Stack* s)
{
    return s->top == -1;
}
int IsStackFull(Stack* s)
{
    return s->top == MAX_N-1;
}

int PushStack(Stack* s, int v)
{
   if(IsStackFull(s))
        return ERROR;
   s->data[++s->top] = v;
   return 1;
}
int TopStack(Stack* s)
{
    if(IsStackEmpty(s))
        return ERROR;
    return s->data[s->top];
}
int PopStack(Stack* s)
{
    if(IsStackEmpty(s))
        return ERROR;
    return s->data[s->top--];
}

//Queue data structure
//队列结构体，BFS需要使用队列
typedef struct Queue_
{
    //队列元素数组
    int data[MAX_N];
    //队列头下标
    int front;
    //队列尾下标
    int rear;
}Queue;
//创建队列
Queue* CreateQueue()
{
    //动态分配队列结构体内存
    Queue* q = (Queue*)malloc(sizeof(Queue));
    //设置头下标和尾下标都为-1，表示当前队列为空
    q->front = q->rear = -1;
    return q;
}
//队列是否为空
int IsQueueEmpty(Queue* q)
{
    return q->front==q->rear;
}
//队列是否满
int IsQueueFull(Queue* q)
{
    return (q->rear+1)%MAX_N == q->front;
}
//入队
int Enque(Queue* q, int v)
{
    //如果队列满了，返回0
    if(IsQueueFull(q))
        return 0;
    //移动队列尾部下标
    q->rear = (q->rear+1)%MAX_N;
    //向队列尾部入队
    q->data[q->rear] = v;
    return 1;
}
//出队
int Deque(Queue* q)
{
    //如果队列为空，则返回错误
    if(IsQueueEmpty(q))
        return ERROR;
    //移动队列头部下标
    q->front = (q->front+1)%MAX_N;
    //返回队列出队的元素值
    return q->data[q->front];
}
//释放队列结构体内存
void FreeQueue(Queue* q)
{
    free(q);
}

//记录顶点访问的标记数组
char visited[MAX_N];

//递归调用的DFS遍历函数，种子顶点为v，遍历结果存储到字符串result中
//该遍历只能搜索到和v在同一连通集的顶点
void DFS_Iterator(MGraph* g, int v, char*result)
{
    int i;
    //临时字符串
    char str[MAX_STR_LEN];

    //设置当前顶点已经访问
    visited[v] = 1;
    //输出访问结果
    sprintf(str, " %d", v);
    strcat(result, str);
    //在邻接矩阵中遍历顶点v的所有未访问的邻接顶点
    for(i=0; i<g->nv; ++i)
    {
        //未访问且和顶点v有边相连，则递归调用
        if(visited[i]==0 && g->matrix[v][i]==1)
            DFS_Iterator(g, i, result);
    }
}

//包装DFS_Iterator递归调用
//DFS_Iterator只能遍历种子顶点所在的连通集，而DFS函数需要从顶点中找出所有未被访问的顶点，
//从而找出图中所有的连通分量
int DFS(MGraph* g)
{
    int i, groupNum=0;
    char result[MAX_STR_LEN];
    //把顶点访问标记数组全部清空为0，表示所有顶点都还未被访问过
    memset(visited, 0, sizeof(visited));
    //遍历顶点集合，找到一个未被访问的顶点，以它为种子点深度优先搜索其所在的连通分量
    for(i=0; i<g->nv; ++i)
    {
        //如果该顶点已被访问过，则不要再访问
        if(visited[i])
            continue;
        //以顶点i为起始点，搜索i所在的联通分量
        //先把结果左括号处理好
        strcpy(result, "{");
        //递归调用深度优先搜索函数
        DFS_Iterator(g, i, result);
        //把结果右括号处理好
        strcat(result, " }");
        //打印连通集合
        printf("%s\n", result);
        //连通集数量+1
        ++groupNum;
    }
    //返回连通分量的数量
    return groupNum;
}

//宽度优先遍历breadth first search
int BFS(MGraph *g)
{
    int i, j, v, groupNum=0;
    char result[MAX_STR_LEN], str[MAX_STR_LEN];
    //创建一个队列
    Queue* q = CreateQueue();
    //把顶点访问标记数组全部清空为0，表示所有顶点都还未被访问过
    memset(visited, 0, sizeof(visited));

    //遍历顶点集合，找到一个未被访问的顶点，以它为种子点宽度优先搜索其所在的连通分量
    for(i=0; i<g->nv; ++i)
    {
        //如果该顶点已被访问过，则不要再访问
        if(visited[i])
            continue;
        //以顶点i为起始点，搜索i所在的联通分量
        //先把结果左括号处理好
        sprintf(result, "{ %d", i);
        //设置当前顶点已经访问
        visited[i] = 1;
        //把顶点i入队
        Enque(q, i);
        //当队列非空
        while(!IsQueueEmpty(q))
        {
            //从队列头部出队一个顶点编号
            v = Deque(q);
            //在邻接矩阵中遍历顶点v的所有未访问的邻接顶点
            for(j=0; j<g->nv; ++j)
            {
                //如果顶点j未被访问过且和顶点v有边相连，则将该顶点入队
                if(visited[j]==0 && g->matrix[v][j]==1)
                {
                    //设置访问标记
                    visited[j]=1;
                    //输出访问结果
                    sprintf(str, " %d", j);
                    strcat(result, str);
                    //顶点j入队
                    Enque(q, j);
                }
            }
        }
        //处理好右括号
        strcat(result, " }");
        //打印结果
        printf("%s\n", result);
        //连通集数量+1
        ++groupNum;
    }
    //释放队列内存
    FreeQueue(q);

    //返回连通分量的数量
    return groupNum;
}

int main()
{
    int N, E, i, v1, v2;

    scanf("%d%d", &N, &E);

    //创建图
    MGraph *graph = CreateGraph(N, E);
    //读入E条边，将其加入图
    for(i=0; i<E; ++i)
    {
        scanf("%d%d", &v1, &v2);
        InsertEdge(graph, v1, v2);
    }

    //深度优先遍历
    DFS(graph);

    //宽度优先遍历
    BFS(graph);

    //释放图内存
    FreeGraph(graph);
    return 0;
}
