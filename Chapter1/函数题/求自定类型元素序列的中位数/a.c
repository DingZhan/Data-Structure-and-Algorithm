//选择排序超时问题，因为没有stdlib.h,所以不能直接使用qsort
ElementType Median( ElementType A[], int N )
{
    int i, j, maxPos;
    ElementType temp;
    for(i=0; i<N; ++i)
    {
        maxPos = i;
        for(j=i+1; j<N; ++j)
        {
            if(A[j]>A[maxPos])
                maxPos = j;
        }
        temp = A[i];
        A[i] = A[maxPos];
        A[maxPos] = temp;
    }
    return A[(N+1)/2-1];
}