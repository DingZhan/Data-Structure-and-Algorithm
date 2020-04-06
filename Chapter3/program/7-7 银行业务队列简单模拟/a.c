#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
typedef struct QItem_
{
    int ID; //排队人的编号
    int finishTime; //排队人业务结束时间
}QItem;
typedef struct Queue_
{
    QItem queue[MAX_N];
    int front;
    int rear;
}Queue;
Queue* CreateQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = 0;
    return q;
}
int IsEmpty(Queue *q)
{
    return q->front == q->rear;
}
int IsFull(Queue *q)
{
    return (q->rear+1)%MAX_N == q->front;
}
int Enque(Queue *q, int ID, int finishTime)
{
    if(IsFull(q))
        return 0;
    q->rear = (q->rear+1)%MAX_N;
    q->queue[q->rear].finishTime= finishTime;
    q->queue[q->rear].ID= ID;
    return 1;
}
int Deque(Queue *q, QItem* item)
{
    if(IsEmpty(q))
        return 0;
    q->front = (q->front+1)%MAX_N;
    item->ID = q->queue[q->front].ID;
    item->finishTime = q->queue[q->front].finishTime;
    return 1;
}
int Front(Queue *q, QItem* item)
{
    if(IsEmpty(q))
        return 0;
    int index = (q->front+1)%MAX_N;
    item->ID = q->queue[index].ID;
    item->finishTime = q->queue[index].finishTime;
    return 1;
}

int main()
{
    //A窗口队列
    Queue *A = CreateQueue();
    //B窗口队列
    Queue *B = CreateQueue();
    //上一个排队人员事务结束时间
    int N, id, i, lastFinishTimeA=0,lastFinishTimeB=0;
    //是否第一次打印，如果第一次打印不需要打印空格
    int bFirst=1;
    QItem itemA, itemB;

    //读入人数
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &id);
        //奇数进入A窗口排队
        if(id%2==1)
        {
            lastFinishTimeA+=1;
            Enque(A, id, lastFinishTimeA);
        }
        else//偶数进入B窗口排队
        {
            lastFinishTimeB+=2;
            Enque(B, id, lastFinishTimeB);
        }
    }

    //同步访问两个队列
    while(!IsEmpty(A) && !IsEmpty(B))
    {
        if(!bFirst)
            printf(" ");
        //A和B都暂不出队列
        //先获得队前的元素
        Front(A, &itemA);
        Front(B, &itemB);
        //比较结束时间
        if(itemA.finishTime<=itemB.finishTime)
        {
            //A队列出列
            Deque(A, &itemA);
            printf("%d", itemA.ID);
        }
        else
        {
            //B队列出列
            Deque(B, &itemB);
            printf("%d", itemB.ID);
        }
        bFirst=0;
    }
    //如果A队列还有人
    while(!IsEmpty(A))
    {
        if(!bFirst)
            printf(" ");
        Deque(A, &itemA);
        printf("%d", itemA.ID);
        bFirst = 0;
    }
    //如果B队列还有人
    while(!IsEmpty(B))
    {
        if(!bFirst)
            printf(" ");
        Deque(B, &itemB);
        printf("%d", itemB.ID);
        bFirst = 0;
    }
    printf("\n");
    return 0;
}
