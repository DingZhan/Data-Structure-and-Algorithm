#include <stdio.h>
#include <stdlib.h>

//最小堆里最多元素个数
#define MAX_N 1001
//最小堆里元素的最小值-1
#define MIN_V -10001

//定义最小堆结构体
typedef struct MinHeap_
{
    //使用数组存储最小堆
    int data[MAX_N];
    //当前堆中元素个数
    int size;
}MinHeap;

//创建最小堆
MinHeap * CreateMinHeap()
{
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    //当前元素个数为0
    heap->size = 0;
    //设置哨兵，guard
    heap->data[0] = MIN_V;
    return heap;
}
//释放最小堆，这里使用二级指针是希望将最小堆指针设置为NULL
void ReleaseMinHeap(MinHeap **heap)
{
    free(*heap);
    *heap = NULL;
}

//创建最小堆方法：添加元素到最小堆
int AddMinHeap(MinHeap *heap, int v)
{
    int i;
    //如果堆已满
    if(heap->size>=MAX_N-1)
        return 0;
    //待插入元素位置i
    i = ++heap->size;
    //不断和父结点值进行比较，直到待插入元素值大于父节点
    for(;v<heap->data[i/2]; i/=2)
        heap->data[i] = heap->data[i/2];
    //将待插入元素设置到相应位置
    heap->data[i] = v;
    return 1;
}

//打印堆中路径
void PrintPath(MinHeap *heap, int id)
{
    int bFirst=1;
    //如果id无效
    if(id>heap->size)
    {
        printf("\n");
        return;
    }
    //不断访问父节点，直到哨兵位置
    for(; id!=0; id/=2)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", heap->data[id]);
        bFirst = 0;
    }
    printf("\n");
}

int main()
{
    int i, N, M, v, id;
    //创建最小堆
    MinHeap *heap = CreateMinHeap();
    scanf("%d%d", &N, &M);
    //读入N个元素，并插入最小堆
    for(i=0; i<N; ++i)
    {
        scanf("%d", &v);
        AddMinHeap(heap, v);
    }
    //读入M个路径查询
    for(i=0; i<M; ++i)
    {
        scanf("%d", &id);
        PrintPath(heap, id);
    }
    //释放最小堆内存
    ReleaseMinHeap(&heap);
    return 0;
}
