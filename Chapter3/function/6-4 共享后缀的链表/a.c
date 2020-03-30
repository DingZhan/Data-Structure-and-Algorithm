
//得到链表长度
int Length(List L)
{
    PtrToNode node = L->Next;
    int len=0;
    while(node)
    {
        ++len;
        node = node->Next;
    }
    return len;
}

//方法1：得到L1和L2长度，长的链表先遍历，遍历到两个链表剩余结点数都一样的情况下
//再同时遍历，然后找共同的结点
PtrToNode Suffix( List L1, List L2 )
{
    PtrToNode node1,node2;
    int len1, len2, i;
    //得到L1链表长度
    len1 = Length(L1);
    //得到L2链表长度
    len2 = Length(L2);

    //准备遍历两个链表
    node1 = L1->Next;
    node2 = L2->Next;
    //如果L1链表长，L1得先遍历len1-len2个结点
    if(len1>len2)
    {
        i = len1-len2;
        while(i--)
            node1 = node1->Next;
    }
    //如果L2链表长，L2得先遍历len2-len1个结点
    else if(len1<len2)
    {
        i = len2-len1;
        while(i--)
            node2 = node2->Next;
    }
    //L1和L2开始同时遍历直到碰到公共结点
    while(node1 && node1!=node2)
    {
        node1 = node1->Next;
        node2 = node2->Next;
    }
    return node1;
}
