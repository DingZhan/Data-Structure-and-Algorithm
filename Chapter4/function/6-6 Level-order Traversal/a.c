#define MAX_NODES 11
typedef struct Queue_
{
    Tree* data[MAX_NODES];
    int front;
    int rear;
}Queue;
Queue* CreateQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = 0;
    return q;
}
int IsEmpty(Queue* q)
{
    return q->front==q->rear;
}
int IsFull(Queue*q)
{
    return (q->rear+1)%MAX_NODES == q->front;
}
int Enque(Queue*q, Tree d)
{
    if(IsFull(q))
        return 0;
    q->rear = (q->rear+1)%MAX_NODES;
    q->data[q->rear] = d;
    return 1;
}
Tree Deque(Queue* q)
{
    if(IsEmpty(q))
        return NULL;
    q->front = (q->front+1)%MAX_NODES;
    return q->data[q->front];
}
void FreeQueue(Queue*q)
{
    free(q);
}
void Level_order ( Tree T, void (*visit)(Tree ThisNode) )
{
    if(!T)
        return;
    Queue* q = CreateQueue();
    Enque(q, T);
    while(!IsEmpty(q))
    {
        T = Deque(q);
        (*visit)(T);
        if(T->Left)
            Enque(q, T->Left);
        if(T->Right)
            Enque(q, T->Right);
    }
    FreeQueue(q);
}