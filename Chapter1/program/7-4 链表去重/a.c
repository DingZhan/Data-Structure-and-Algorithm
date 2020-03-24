#include <stdio.h>

//定义链表数组的结构体表示，这里用数组模拟链表
typedef struct _Node
{
    int key;
    int next;
}Node;

//链表最大长度地址
#define MAX_N 100001
//链表元素最大值
#define MAX_KEY 10001

int main()
{
    //链表数组，用数组模拟链表
    Node nodes[MAX_N];
    //记号数组，用于表示链表结点元素值是否以前出现过，初始都未出现过
    char bTakens[MAX_KEY]={0};
    //startAddress表示链表起始地址, dupNodeStartAddress表示重复元素链表起始地址，初始为空，dupNodePreAddress表示重复元素链表最后一个结点
    int startAddress, address, key, next, N, i, dupNodeStartAddress=-1, dupNodePreAddress=-1;
    //是否是第一次打印
    int bPrintNext=0;
    //读入链表头地址和结点数
    scanf("%d%d", &startAddress, &N);
    
    //读入N个结点
    for(i=0; i<N; ++i)
    {
        scanf("%d%d%d", &address, &key, &next);
        nodes[address].key = key;
        nodes[address].next = next;
    }
    //如果链表本身是空则退出
    if(startAddress==-1)
        return 0;
    
    while(1)
    {
        //读入当前结点值
        key = nodes[startAddress].key;
        //如果该值已经出现在之前的结点中，则需要将结点移动到另一个重复元素链表中
        if(bTakens[key>=0?key:-key])
        {
            //如果重复元素链表为空，则该结点就是新链表的头结点
            if(dupNodeStartAddress==-1)
                dupNodeStartAddress = startAddress;
            else //否则将该元素挂载到重复元素链表尾部                
                nodes[dupNodePreAddress].next = startAddress;
            //刷新重复元素链表的最后一个结点
            dupNodePreAddress = startAddress;
            //移动当前结点
            startAddress = nodes[startAddress].next;
            //设置重复元素链表的最后一个结点的next指针为空
            if(dupNodePreAddress!=-1)
                nodes[dupNodePreAddress].next = -1;
        }
        else //当前结点值之前没有出现过
        {
            //先打印上一行的next指针为自己
            if(bPrintNext)
                printf(" %05d\n",startAddress);
            //设置该值出现标记
            bTakens[key>=0?key:-key] = 1;
            //打印该链表地址和值，它的next不能打印，必须放到后面
            printf("%05d %d", startAddress, nodes[startAddress].key);
            bPrintNext = 1;
            startAddress = nodes[startAddress].next;
        }
        if(startAddress==-1)
            break;
    }
    //打印最后的next指针，即空指针
    if(bPrintNext)
        printf(" -1\n");

    //打印重复链表中的所有元素
    startAddress = dupNodeStartAddress;
    while(startAddress!=-1)
    {
        printf("%05d %d", startAddress, nodes[startAddress].key);
        if(nodes[startAddress].next==-1)
            printf(" -1\n");
        else
            printf(" %05d\n", nodes[startAddress].next);
        startAddress = nodes[startAddress].next;
    }

	return 0;
}
