#include <stdio.h>

#define MAX_N 1000

int main()
{
    int s[MAX_N],boxes[MAX_N],id[MAX_N],i, j, N, sum=0, nb;

    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", s+i);
        boxes[i]= 100;
    }
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
        {
            if(s[i]<=boxes[j])
            {
                boxes[j]-=s[i];
                id[i] = j;
                break;
            }
        }
    }
    for(i=0, nb=0; i<N; ++i)
    {
        printf("%d %d\n", s[i], id[i]+1);
        if(boxes[i]!=100)
            ++nb;
    }
    printf("%d\n", nb);
    return 0;
}


