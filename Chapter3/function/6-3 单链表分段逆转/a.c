
//逆转 [firstNode, lastNode] 成 [lastNode, firstNode]
PtrToNode Reverse(PtrToNode first, PtrToNode last)
{
    PtrToNode current=first, pre=NULL, next, lastNext;
    //终止逆转位置
    lastNext = last->Next;
    //当前结点没有到终止位置
    while(current!=lastNext)
    {
        next = current->Next;
        current->Next = pre;
        pre = current;
        current = next;
    }
    //把新尾部的Next指向原来尾部的下一个结点
    first->Next = lastNext;
    return last;
}

void K_Reverse( List L, int K )
{
    //逆转区间[firstNode, lastNode], 而preNode->next = firstNode;
    PtrToNode node, firstNode, lastNode, preNode, nextNode;
    //计数当前区间的结点数
    int n=0;
    //遍历结点起点
    node = L->Next;
    //遍历区间的起始结点
    firstNode = node;
    //遍历区间起始结点之前的一个结点
    preNode = L;
    while(node)
    {
        ++n;
        //达到区间上限
        if(n==K)
        {
            //逆转区间的终结点
            lastNode  = node;
            //保存区间的下一个结点
            nextNode = node->Next;
            //计数器清零
            n=0;
            //逆转结点区间 [firstNode, lastNode] 成 [lastNode, firstNode]
            Reverse(firstNode, lastNode);
            //把逆转链表区间的头部挂载到preNode后面
            preNode->Next = lastNode;
            //设置下一段区间的头部的前一个结点
            preNode = firstNode;
            //设置下一个新区间的起始结点
            firstNode = nextNode;
            //遍历下一个结点
            node = nextNode;
        }
        else
            //没达到区间上限，遍历下一个结点
            node = node->Next;
    }
}