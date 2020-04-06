#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001

int main()
{
    //用数组模拟队列
    //A窗口队列
    int A[MAX_N];
    //B窗口队列
    int B[MAX_N];
    int iA, iB, sizeA=0, sizeB=0, N, id, i;
    //是否第一次打印，如果第一次打印不需要打印空格
    int bFirst=1;

    //读入人数
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &id);
        //用位与操作判断奇偶，奇数进入A窗口排队
        if(id&1)
            A[sizeA++] = id;
        else//偶数进入B窗口排队
            B[sizeB++] = id;
    }

    //用游标iA, iB同步访问两个队列
    for(iA=0, iB=0; iA<sizeA && iB<sizeB;)
    {
        if(!bFirst)
            printf(" ");
        //先打印A队列结束服务的人
        printf("%d", A[iA++]);
        //如果A队列还有人，则打印他
        if(iA<sizeA)
            printf(" %d", A[iA++]);
        //接着打印B队列结束服务的人
        printf(" %d", B[iB++]);
        bFirst=0;
    }
    //如果A队列还有人
    while(iA<sizeA)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", A[iA++]);
        bFirst = 0;
    }
    //如果B队列还有人
    while(iB<sizeB)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", B[iB++]);
        bFirst = 0;
    }
    printf("\n");
    return 0;
}