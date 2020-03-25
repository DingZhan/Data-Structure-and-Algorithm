#include <stdio.h>


int main()
{
    int i, N, data, A1=0, A2=0, A3=0, A3Count=0, r;

    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &data);
        r = data%3;
        if(r==0)
        {
            if(data>A1)
                A1 = data;
        }
        else if(r==1)
            ++A2;
        else
        {
            A3+=data;
            ++A3Count;
        }
    }
    if(A1==0)
        printf("NONE");
    else
        printf("%d", A1);
    if(A2==0)
        printf(" NONE");
    else
        printf(" %d", A2);
    if(A3Count==0)
        printf(" NONE");
    else
        printf(" %.1f", (A3+0.0)/A3Count);
    return 0;
}
