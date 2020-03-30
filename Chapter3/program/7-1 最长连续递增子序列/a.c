#include <stdio.h>

#define MAX_N 100001
int main()
{
    int n, i, start, end, data[MAX_N];
    int maxStart=0, maxEnd=0;

    scanf("%d", &n);
    if(n==0)
        return 0;
    scanf("%d", data+0);
    start = 0;
    for(i=1; i<n; ++i)
    {
        scanf("%d", data+i);
        if(data[i]<=data[i-1])
        {
            end = i-1;
            if(end-start>maxEnd-maxStart)
            {
                maxStart = start;
                maxEnd = end;
            }
            start = end = i;
        }
    }
    if(start!=n-1)
    {
        end = n-1;
        if(end-start>maxEnd-maxStart)
        {
            maxStart = start;
            maxEnd = end;
        }
    }
    for(i=maxStart; i<=maxEnd; ++i)
    {
        if(i!=maxStart)
            printf(" ");
        printf("%d", data[i]);
    }
    printf("\n");
    return 0;
}