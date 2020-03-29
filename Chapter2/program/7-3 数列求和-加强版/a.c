#include <stdio.h>

#define MAX_N 100001

//溢出版本
//递归公式Sum(A,N) = Sum(A, N-1)*10 + N*A;
//但绝对不能使用递归方法，因为N最大为10万，一定会使堆栈撑爆

//方法1：
//归纳：个位上的A有N个，十位上的A有N-1个，。。。，最高位上的A有1个
//导致问题，大数越界
unsigned long long Sum(int A, int N)
{
    unsigned long long s=0;
    int i;
    for(i=0; i<N; ++i)
        s = s*10+A*(i+1);
    return s;
}

//递归公式Sum(A,N) = Sum(A, N-1)*10 + N*A;
//大数加法, 15分，超时
void Sum2(int A, int N)
{
    int i, j, s[MAX_N]={0}, b, e, t, sbits=-1;
    for(i=0; i<N; ++i)
    {
        //s = s*10
        for(j=sbits; j>=0; --j)
            s[j+1] = s[j];
        s[0] = 0;

        ++sbits;

        //另一个需要加的大数
        b = (i+1)*A;
        //进位
        e = 0;
        j=0;
        //大数加法
        //s = s + b;
        while(b)
        {
            //t <= s[j] + b[j] + e;
            t = s[j] + b%10 + e;
            s[j] = t%10;
            //更新进位
            e = t/10;
            b/=10;
            ++j;
        }
        while(e)
        {
            t = s[j]+e;
            s[j] = t%10;
            e = t/10;
            ++j;
        }
        sbits = (j-1>sbits)?(j-1):sbits;
    }
    if(sbits==-1)
        printf("0");
    else
    {
        for(i=sbits; i>=0; --i)
            printf("%d", s[i]);
    }
    printf("\n");
}

/*
f(A,N) = f(A,N-1)*10+N*A
  = (f(A,N-2)*10+(N-1)*A)*10 + N*A
  = f(A, N-2)*10^2 + A*(10^1*(N-1)+10^0*N)
  ...
  = A*(10^(N-1)*1 + 10^(N-2)*2 + 10^(N-3)*3 + ... +10^1*(N-1) + N);

*/
//f(A, N) = A*10^(N-1)*1 + A*(10^(N-2)*2 + 10^(N-3)*3 + ... +10^1*(N-1) + N);

//大数加法, 淳朴的大数加法
//16分，运行超时
void Sum3(int A, int N)
{
    int i, j, e, t, s[MAX_N]={0}, a[MAX_N], smaxpos=-1;
    for(i=0; i<N; ++i)
        a[i] = A;
    e = 0;
    for(i=0; i<N; ++i)
    {
        if(i>smaxpos)
            smaxpos = i;
        for(j=0; j<=i; ++j)
        {
            t = s[j] + a[j] + e;
            s[j] = t%10;
            e = t/10;
        }
        while(e)
        {
            t = s[j] + e;
            s[j] = t%10;
            e = t/10;
            smaxpos = (j>smaxpos)?j:smaxpos;
            ++j;
        }
    }
    if(smaxpos==-1)
        printf("0");
    else
    {
        for(i=smaxpos; i>=0; --i)
        {
            printf("%d", s[i]);
        }
    }
    printf("\n");
    return ;
}

//归纳：个位上的A有N个，十位上的A有N-1个，。。。，最高位上的A有1个
//因此利用进位方法将时间复杂度降到O(N)
void Sum4(int A, int N)
{
    int i, n, e, s[MAX_N]={0};
    e = 0;
    for(i=0; i<N; ++i)
    {
        //每一位上的和（含上一次的进位值）
        e = A*(N-i)+e;
        //当前位的值
        s[i] = e%10;
        //新的进位值
        e/=10;
    }
    //最高位如果还有进位，则累加到s中
    if(e)
    {
        n = N+1;
        s[N] = e;
    }
    else
        n = N;
    if(n==0)
        printf("0");
    else
    {
        for(i=n-1; i>=0; --i)
            printf("%d", s[i]);
    }
    printf("\n");
    return ;
}
int main()
{
    int A, N;
    scanf("%d%d", &A, &N);
    //printf("%lld\n", Sum(A, N));
    Sum4(A, N);
    return 0;
}
