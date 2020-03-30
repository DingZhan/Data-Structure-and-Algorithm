ElementType Find( List L, int m )
{
    PtrToNode mthNode=NULL, node;
    //因为L带头结点，所以node为L的next，否则为L
    node =L->Next;
    //遍历链表
    while(node)
    {
        //将计数器减一
        --m;
        //如果当前计数器为0，表示正好访问过m个结点，那么第一个结点就是当前的倒数第m个结点
        if(m==0)
            mthNode = L->Next;
        //如果计数器为负，则表示要把倒数第m个结点往后挪一个结点
        else if(m<0)
            mthNode = mthNode->Next;
        //当前结点正常遍历
        node = node->Next;
    }
    //如果倒数第m个结点存在
    if(mthNode)
        return mthNode->Data;
    else
        return ERROR;
}