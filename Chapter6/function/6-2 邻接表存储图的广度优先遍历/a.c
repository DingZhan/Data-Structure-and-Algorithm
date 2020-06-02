//BFS需要队列数据结构，这里定义循环队列结构体
typedef struct Queue_
{
    //队列中元素是顶点标号
   Vertex *vertices;
    //队列最大长度
   int size;
    //队列前和后下标
   int front, rear;
}Queue;

//创建队列
Queue* CreateQueue(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    //实际容量+1
    size+=1;
    //动态分配队列数组
    q->vertices = (Vertex*)malloc(sizeof(Vertex)*size);
    //初始front和rear都为0
    q->front = q->rear  =0;
    //设置队列长度
    q->size = size;
    return q;
}

//释放队列内存
void FreeQueue(Queue* q)
{
    //释放顶点数组
    free(q->vertices);
    q->vertices = NULL;
    //释放队列
    free(q);
}

//队列是否为空
int IsQueueEmpty(Queue *q)
{
    return q->front == q->rear;
}

//队列是否为满
int IsQueueFull(Queue *q)
{
    return (q->rear+1)%q->size == q->front;
}

//入队
void Enqueue(Queue*q, Vertex v)
{
    if(IsQueueFull(q))
        return;
    q->rear = (q->rear+1)%q->size;
    q->vertices[q->rear] = v;
}
//出队
Vertex Dequeue(Queue *q)
{
    if(IsQueueEmpty(q))
        return -1;
    q->front = (q->front+1)%q->size;
    return q->vertices[q->front];
}

//宽度优先遍历，S作为种子顶点
void BFS ( LGraph Graph, Vertex S, void (*Visit)(Vertex) )
{
    //创建BFS顶点队列
    Queue* q = CreateQueue(MaxVertexNum);
    PtrToAdjVNode node;

    //设置当前顶点V被访问
    Visited[S] =  true;
    //访问顶点V
    Visit(S);
    //将S入队
    Enqueue(q, S);
    //当队列不为空
    while(!IsQueueEmpty(q))
    {
        //出队一个顶点
        S = Dequeue(q);
        //访问该顶点邻接边链表
        node = Graph->G[S].FirstEdge;//->Next;
        //访问链表
        while(node)
        {
            //如果邻接顶点未被访问过，则访问它
            if(Visited[node->AdjV]==false)
            {
                Visited[node->AdjV] = true;
                Visit(node->AdjV);
                //入队
                Enqueue(q, node->AdjV);
            }
            //遍历下一个结点
            node = node->Next;
        }
    }
    //释放队列
    FreeQueue(q);
}