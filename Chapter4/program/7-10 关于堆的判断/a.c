#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 21
#define MIN_VALUE -10001
#define ERROR -10001

//定义最小堆结构体
typedef struct Heap_
{
    int data[MAX_N];
    int size;
}MinHeap;

//创建最小堆
MinHeap* CreateMinHeap()
{
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    //哨兵
    heap->data[0] = MIN_VALUE;
    //初始堆为空
    heap->size = 0;
    return heap;
}
//添加元素加入到最小堆
void AddToMinHeap(MinHeap *heap, int value)
{
    int i;
    //添加位置
    i = ++heap->size;
    //向上比较
    for(;heap->data[i/2]>value; i/=2)
        heap->data[i]=heap->data[i/2];
    heap->data[i] = value;
}
//释放最小堆内存
void FreeMinHeap(MinHeap* heap)
{
    free(heap);
}
//得到最小堆根结点值
int GetRoot(MinHeap*heap)
{
    //如果堆为空，返回错误标记
    if(heap->size==0)
        return ERROR;
    return heap->data[1];
}

//得到某个值在堆中的索引号
int GetIndex(MinHeap*heap, int value)
{
    int i;
    for(i=1; i<=heap->size; ++i)
    {
        if(heap->data[i]==value)
            return i;
    }
    //没找到返回错误标记
    return ERROR;
}

//判断两个值是兄弟关系，即判断是否拥有同一个父节点
int IsSibling(MinHeap* heap, int data1, int data2)
{
    int id1 = GetIndex(heap, data1);
    if(id1==ERROR)
        return 0;
    int id2 = GetIndex(heap, data2);
    if(id2==ERROR)
        return 0;
    return id1/2==id2/2;
}

//是否是父子关系
int IsParent(MinHeap* heap, int parent, int child)
{
    int parentID = GetIndex(heap, parent);
    if(parentID==ERROR)
        return 0;
    int childID = GetIndex(heap, child);
    if(childID==ERROR)
        return 0;
    return parentID==childID/2;
}

int main()
{
    int M, N, i, value, v1, v2;
    char str[256], str2[256], *t;
    MinHeap *heap;

    //创建最小堆
    heap = CreateMinHeap();
    scanf("%d%d", &N, &M);
    //把数据加入堆
    for(i=0; i<N; ++i)
    {
        scanf("%d", &value);
        AddToMinHeap(heap, value);
    }
    //吃掉回车
    fgets(str, 256, stdin);

    //遍历M次查询
    for(i=0; i<M; ++i)
    {
        fgets(str, 256, stdin);
        //查询是否是根结点
        if(strstr(str, "is the root")!=NULL)
        {
            value = atoi(str);
            if(GetRoot(heap)==value)
                printf("T\n");
            else
                printf("F\n");
        }
        //是否是兄弟关系
        else if(strstr(str, "are siblings")!=NULL)
        {
            sscanf(str, "%d%s%d", &v1, str2, &v2);
            if(IsSibling(heap, v1, v2))
                printf("T\n");
            else
                printf("F\n");
        }
        //是否是父子关系
        else if((t=strstr(str, "parent"))!=NULL)
        {
            v1 = atoi(str);
            //9是"parent of"的偏移量
            v2 = atoi(t+9);
            if(IsParent(heap, v1, v2))
                printf("T\n");
            else
                printf("F\n");
        }
        //是否是子父关系
        else if((t=strstr(str, "child"))!=NULL)
        {
            v1 = atoi(str);
            //8是"child of"的偏移量
            v2 = atoi(t+8);
            if(IsParent(heap, v2, v1))
                printf("T\n");
            else
                printf("F\n");
        }
    }
    //释放堆
    FreeMinHeap(heap);
    return 0;
}
