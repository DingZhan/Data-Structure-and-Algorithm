#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, d, K, sum=0, maxSum=0;
    scanf("%d", &K);
    for(i=0; i<K; ++i)
    {
        scanf("%d", &d);
        sum+=d;
        if(sum<0)
            sum = 0;
        else if(sum>maxSum)
            maxSum = sum;
    }
    printf("%d", maxSum);
    return 0;
}
