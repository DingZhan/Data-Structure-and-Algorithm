#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 12

//graph structure: neighbor matrix
typedef struct MGraph_
{
    int N, E;
    int m[MAX_N][MAX_N];
}MGraph;

//depth first search
void DFS(MGraph*graph, int v, bool *visits)
{
    int i;
    printf(" %d", v);
    visits[v] = true;
    for(i=0; i<graph->N; ++i)
    {
        if(!visits[i] && graph->m[v][i])
        {
            DFS(graph, i, visits);
        }
    }
}

//depth first search main calling
void DFSTraverse(MGraph* graph)
{
    bool visits[MAX_N]={false};
    int i;
    for(i=0; i<graph->N; ++i)
    {
        if(!visits[i])
        {
            printf("{");
            DFS(graph, i, visits);
            printf(" }\n");
        }
    }
}

#define INVALID_DATA -1000
typedef struct Queue_
{
    int data[MAX_N];
    int front, rear;
}Queue;

Queue* CreateQueue()
{
    Queue *queue =(Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}
void FreeQueue(Queue* queue)
{
    free(queue);
}
bool IsEmpty(Queue* queue)
{
    return queue->front==queue->rear;
}
bool IsFull(Queue* queue)
{
    return (queue->rear+1)%MAX_N == queue->front;
}
bool Enque(Queue* queue, int v)
{
    if(IsFull(queue))
        return false;
    queue->rear = (queue->rear +1) %MAX_N;
    queue->data[queue->rear] = v;
    return true;
}
int Deque(Queue* queue)
{
    if(IsEmpty(queue))
        return INVALID_DATA;
    queue->front = (queue->front +1) %MAX_N;
    return queue->data[queue->front];
}



void BFS(MGraph* graph)
{
    Queue* queue = CreateQueue();
    int i, j, v;
    bool visits[MAX_N] = {false};
    for(i=0; i<graph->N; ++i)
    {
        if(visits[i])
            continue;
        printf("{");
        visits[i] = true;
        Enque(queue, i);
        while(!IsEmpty(queue))
        {
            v = Deque(queue);
            printf(" %d", v);
            for(j=0; j<graph->N; ++j)
            {
                if(!visits[j] && graph->m[v][j])
                {
                    visits[j] = true;
                    Enque(queue, j);
                }
            }
        }
        printf(" }\n");
    }

    FreeQueue(queue);
}
int main()
{
    MGraph *graph = (MGraph*)malloc(sizeof(MGraph));
    int i, j, v1, v2;
    scanf("%d%d", &graph->N, &graph->E);
    for(i=0; i<graph->E; ++i)
    {
        scanf("%d%d", &v1, &v2);
        graph->m[v1][v2] = 1;
        graph->m[v2][v1] = 1;
    }

    DFSTraverse(graph);

    BFS(graph);
    return 0;
}
