#include <stdio.h>
#include <stdlib.h>

//用最小堆解决这个问题

//堆最大元素个数
#define MAX_N 10001
//最小堆，所以需要一个最小值做哨兵
#define MIN_VALUE 0
//无效值
#define ERROR_VALUE -1

//最小堆结构体，这里使用一个数组存放元素
typedef struct Heap_
{
    int data[MAX_N];
    //堆中元素个数
    int size;
}MinHeap;

//创建最小堆
MinHeap* CreateMinHeap()
{
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    //初始化元素个数为0
    heap->size=0;
    //设置哨兵
    heap->data[0] = MIN_VALUE;
    return heap;
}

//往最小堆添加元素
void AddToMinHeap(MinHeap* heap, int value)
{
    //新加元素位置
    int i = ++heap->size;
    //向上比较
    for(;heap->data[i/2]>value; i/=2)
        heap->data[i] = heap->data[i/2];
    //填充该值
    heap->data[i] = value;
}

//从堆顶删除一个元素
int PopFromMinHeap(MinHeap* heap)
{
    //如果堆为空，则返回错误
    if(IsMinHeapEmpty(heap))
        return ERROR_VALUE;
    //保存堆顶值
    int rootValue = heap->data[1];
    //将最后一个元素设置到堆顶（不是实际设置）
    int value = heap->data[heap->size--];
    int i, tag=0;
    //向下比较，把左右儿子的最小值上提
    for(i=1;2*i<=heap->size; )
    {
        //右儿子标记
        tag = 0;
        //如果有右儿子，则判断左右儿子的最小值
        if(2*i+1<=heap->size)
        {
            if(heap->data[2*i]>heap->data[2*i+1])
                tag = 1;
        }
        //如果儿子值比父亲值小，则交换（实际不交换，只上移）
        if(heap->data[2*i+tag]<value)
        {
            //上移
            heap->data[i] = heap->data[2*i+tag];
        }
        else
            break;
        //继续向下比较
        i = 2*i+tag;
    }
    //设置最后一个元素值
    heap->data[i] = value;
    return rootValue;
}

//堆是否为空
int IsMinHeapEmpty(MinHeap* heap)
{
    return heap->size==0;
}

//得到堆中元素个数
int GetMinHeapSize(MinHeap* heap)
{
    return heap->size;
}

//释放堆内存
void FreeMinHeap(MinHeap* heap)
{
    free(heap);
}

int main()
{
    int N, i, v, v1, v2, sum=0;
    //创建最小堆
    MinHeap *heap = CreateMinHeap();
    //读入数据量
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &v);
        //加入最小堆
        AddToMinHeap(heap, v);
    }
    //当堆中元素个数大于1
    while(GetMinHeapSize(heap)>1)
    {
        //弹出两个堆顶元素
        v1 = PopFromMinHeap(heap);
        v2 = PopFromMinHeap(heap);
        //把累加和重新加入堆
        AddToMinHeap(heap, v1+v2);
        //累计累加和
        sum+=v1+v2;
    }
    //释放最小堆
    FreeMinHeap(heap);
    printf("%d\n", sum);
    return 0;
}
