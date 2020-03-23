#include <stdio.h>
#include <stdlib.h>

/*
6
0 0 0 1 2 -3
6
0 0 0 0 0 0
*/
int main()
{
    int i, d, K, sum=0, maxSum=0;
    //startValue表示有效区间的起始值，maxSumStartValue和maxSumEndValue表示最大子列和区间的起始值和终止值
    //firstValue和lastValue表示整个区间的第一个和最后一个元素值
    int startValue, maxSumStartValue=0, maxSumEndValue=0, firstValue, lastValue;
    //allNegative表示是否所有元素都为负数，初始为yes
    //bResetStartValue表示是否需要重新记录子列和的第一个元素值，初始为yes
    int allNegative=1, bResetStartValue=1;
    scanf("%d", &K);
    for(i=0; i<K; ++i)
    {
        scanf("%d", &d);
        if(i==0)
            firstValue = d;
        else if(i==K-1)
            lastValue = d;
        if(d>=0)
            allNegative = 0;
        //设置子列和区间的起始值
        if(bResetStartValue && d>=0)
        {
            startValue = d;
            bResetStartValue = 0;
        }
        sum+=d;
        if(sum<0)
        {
            sum = 0;
            //需要将下一个有效的元素设置为子列和区间的起始值
            bResetStartValue = 1;
        }
        else if(sum>maxSum)
        {
            maxSum = sum;
            maxSumStartValue = startValue;
            maxSumEndValue = d;
        }
    }
    if(allNegative)
    {
        maxSum = 0;
        maxSumStartValue = firstValue;
        maxSumEndValue = lastValue;
    }
    printf("%d %d %d", maxSum, maxSumStartValue, maxSumEndValue);
    return 0;
}
