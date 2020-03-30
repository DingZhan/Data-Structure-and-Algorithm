List Delete( List L, ElementType minD, ElementType maxD )
{
    int i, j;
    //两个步进器，i正常走，j可能走的慢一些(只有需要留在线性表的元素才需要往后走一步)
    for(i=0,j=0; i<=L->Last; ++i)
    {
        if(L->Data[i]<=minD || L->Data[i]>=maxD)
        {
            L->Data[j] = L->Data[i];
            ++j;
        }
    }
    //刷新最后一个元素位置
    L->Last = j-1;
    return L;
}