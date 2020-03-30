//最后一个测试点超时问题
List Delete( List L, ElementType minD, ElementType maxD )
{
    int i, j;
    for(i=0; i<=L->Last; ++i)
    {
        if(L->Data[i]>minD && L->Data[i]<maxD)
        {
            for(j=i; j<L->Last; ++j)
            {
                L->Data[j] = L->Data[j+1];
            }
            --L->Last;
            --i;
        }
    }
    return L;
}