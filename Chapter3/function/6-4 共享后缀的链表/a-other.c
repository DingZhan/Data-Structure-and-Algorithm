//逆转链表
void Reverse(List L)
{
    PtrToNode current, pre=NULL, next;
    pre = NULL;
    current = L->Next;
    while(current)
    {
        next = current->Next;
        current->Next = pre;
        pre = current;
        current = next;
    }
    L->Next = pre;
}

//公共值后缀，结点内容相同的公共后缀获得方法
//这不是题目要求的内容，只是提供了一种公共值后缀的解法
PtrToNode SuffixValue( List L1, List L2 )
{
    PtrToNode node1,node2, suffixNode=NULL;
    //逆转L1链表
    Reverse(L1);
    Reverse(L2);
    node1 = L1->Next;
    node2 = L2->Next;
    while(node1 && node2 && node1->Data==node2->Data)
    {
        suffixNode = node1;
        node1 = node1->Next;
        node2 = node2->Next;
    }
    Reverse(L1);
    Reverse(L2);
    return suffixNode;
}