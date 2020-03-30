//方法1：弄脏L1链表中的所有数据，然后遍历L2链表，遍历过程中发现的第一个脏数据的结点即是公共后缀结点的起始结点
PtrToNode Suffix( List L1, List L2 )
{
    PtrToNode node1,node2;
    //弄脏L1结点中数据
    node1 = L1->Next;
    while(node1)
    {
        node1->Data = -node1->Data;
        node1 = node1->Next;
    }
    //遍历L2链表，遍历过程中发现的第一个脏数据的结点即是公共后缀结点的起始结点
    //否则公共结点为NULL
    node2 = L2->Next;
    while(node2)
    {
        //发现脏数据
        if(node2->Data<0)
            break;
        node2 = node2->Next;
    }
    //还原L1结点中数据
    node1 = L1->Next;
    while(node1)
    {
        node1->Data = -node1->Data;
        node1 = node1->Next;
    }
    //node2要么为公共后缀结点的起始结点，要么为NULL
    return node2;
}
