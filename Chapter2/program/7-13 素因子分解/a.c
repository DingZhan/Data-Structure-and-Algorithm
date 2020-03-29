#include <stdio.h>
#include <math.h>
int IsPrime(int n)
{
    int t, i;
    if(n<2)
        return 0;
    t = sqrt(n);
    for(i=2; i<=t; ++i)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}

typedef struct Factor_
{
    int p;
    int k;
}Factor;

void Decompose(int N, Factor fs[], int *fsNum)
{
    if(N==1)
    {
        (*fsNum)=1;
        fs[0].k=1;
        fs[0].p=1;
        return;
    }
    int i;
    for(i=2; i<=N; )
    {
        //如果i是N的因子，并且是质数
        if(N%i==0 && IsPrime(i))
        {
            //将该因子存储到结构体数组中
            if((*fsNum)>0 && fs[(*fsNum)-1].p==i)
                ++fs[(*fsNum)-1].k;
            else
            {
                fs[*fsNum].p = i;
                fs[*fsNum].k = 1;
                ++(*fsNum);
            }
            //将N除以因子
            N/=i;
            //如果i是素因子，则继续使用i测试
        }
        else
            ++i;
    }
}
int main ()
{
    Factor fs[10000];
    int fsNum=0,i, N;

    scanf("%d", &N);

    Decompose(N, fs, &fsNum);

    printf("%d=", N);
    for(i=0; i<fsNum; ++i)
    {
        if(i!=0)
            printf("*");
        if(fs[i].k==1)
            printf("%d", fs[i].p);
        else
            printf("%d^%d", fs[i].p, fs[i].k);
    }
    printf("\n");
    return 0;
}
