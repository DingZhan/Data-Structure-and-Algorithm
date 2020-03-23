#include <stdio.h>

#define MAXN 100001

int main()
{
    //为了节省一个数组S2[MAXN],这里使用needS2Data表示是否需要scanf下一个S2元素，该值
    //存储在变量s2data中，而lastValue表示上一个S1和S2同步扫描的值
    int N, i, j, S1[MAXN],  k, needS2Data=1, s2data, lastValue;

    scanf("%d", &N);
    //中位数下标
    k = (2*N+1)/2-1;

    //读入S1数组
    for(i=0; i<N; ++i)
        scanf("%d", S1+i);

    //同步扫描S1和S2数组，为了节省S2数组内存，我们用needS2Data和s2data
    //i表示S1数组扫描的下标，j表示S2数组扫描的下标，每扫描一个元素后，k递减1
    for(i=0, j=0; k>=0; k--)
    {
        //需要读取S2一个元素
        if(needS2Data)
        {
            needS2Data = 0;
            scanf("%d", &s2data);
        }
        //S1和S2都没有扫描完毕，由于S1和S2长度都一样，所以这里貌似不需要这个下标保护
        //但通用的做法一定需要下标保护，防止数组访问越界
        if(j<N && i<N)
        {
            //S2[j]<=S1[i],所以还要继续读取下一个S2元素，j下标递增，i不变
            if(s2data<=S1[i])
            {
                needS2Data=1;
                ++j;
                lastValue = s2data;
            }
            else //继续读取下一个S1元素，i下标递增，j不变
            {
                lastValue = S1[i];
                ++i;
            }
        }
        else
        {
            //S1还没扫描完毕
            if(i<N)
            {
                lastValue = S1[i];
                ++i;
            }
            else //S2还没扫描完毕
            {
                lastValue = s2data;
                ++j;
                needS2Data=1;
            }
        }
    }
    printf("%d\n", lastValue);
    return 0;
}
