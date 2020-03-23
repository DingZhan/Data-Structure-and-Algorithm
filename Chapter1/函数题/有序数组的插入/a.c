
bool Insert( List L, ElementType X )
{
    int begin=0, end= L->Last, mid, i, lastValidPos=-1;
    if(L->Last==MAXSIZE-1)
      return false;
    while(begin<=end)
    {
        mid = begin+(end-begin)/2;
        if(X==L->Data[mid])
        {
            return false;
        }
        else if(X<L->Data[mid])
        {
            begin = mid+1;
        }
        else
        {
            end = mid-1;
            lastValidPos = mid;
        }
    }
    if(lastValidPos==-1)
        lastValidPos = L->Last+1;

    for(i=L->Last; i>=lastValidPos; --i)
    {
        L->Data[i+1] = L->Data[i];
    }
    L->Data[lastValidPos]=X;
    ++L->Last;
    return true;
}
