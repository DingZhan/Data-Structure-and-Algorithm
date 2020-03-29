#include <stdio.h>

#define MAX_N 10

int main()
{
    int data[MAX_N],i, j, N, sum=0;

    scanf("%d", &N);
    for(i=0; i<N; ++i)
        scanf("%d", data+i);
    for(i=0; i<N; ++i)
    {
        for(j=0; j<N; ++j)
        {
            if(j==i)
                continue;
            sum+=data[i]*10+data[j];
        }
    }
    printf("%d\n", sum);
    return 0;
}


