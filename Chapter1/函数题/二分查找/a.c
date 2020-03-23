Position BinarySearch( List L, ElementType X )
{
    int begin = 1, end = L->Last, mid;
    while(begin<=end)
    {
        mid = begin+(end-begin)/2;
        if(L->Data[mid]==X)
        {
            return mid;
        }
        else if(L->Data[mid]<X)
        {
            begin = mid+1;
        }
        else
        {
            end = mid-1;
        }
    }   
    return NotFound;
}