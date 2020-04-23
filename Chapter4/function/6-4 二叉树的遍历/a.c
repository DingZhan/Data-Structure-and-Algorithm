
void InorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    InorderTraversal(BT->Left);
    printf(" %c", BT->Data);
    InorderTraversal(BT->Right);
}
void PreorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    printf(" %c", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}
void PostorderTraversal( BinTree BT )
{
    if(!BT)
        return;
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %c", BT->Data);
}

#define MAX_N 10000
typedef struct MyQueue_
{
    Position Data[MAX_N];
    int front;
    int rear;
}MyQueue;

MyQueue* CreateQueue()
{
    MyQueue *q = (MyQueue*)malloc(sizeof(MyQueue));
    q->front = q->rear = 0;
    return q;
}
int IsQueueFull(MyQueue *q)
{
    return (q->rear+1)%MAX_N == q->front;
}
int IsQueueEmpty(MyQueue *q)
{
    return q->front == q->rear;
}

int Enque(MyQueue*q , Position data)
{
    if(IsQueueFull(q))
        return 0;
    q->rear = (q->rear+1)%MAX_N;
    q->Data[q->rear] = data;
    return 1;
}

Position Deque(MyQueue*q)
{
    if(IsQueueEmpty(q))
        return NULL;
    q->front = (q->front+1)%MAX_N;
    return q->Data[q->front];
}

void FreeQueue(MyQueue*q)
{
    free(q);
}

void LevelorderTraversal( BinTree BT )
{
    Position node;
    MyQueue * q;
    if(!BT)
        return;
    q = CreateQueue();
    Enque(q, BT);
    while(!IsQueueEmpty(q))
    {
        node = Deque(q);
        printf(" %c", node->Data);
        if(node->Left)
            Enque(q, node->Left);
        if(node->Right)
            Enque(q, node->Right);
    }

    FreeQueue(q);
}
