#include <stdio.h>

#define MAX_E 1001
#define MAX_E2 2002

typedef struct Poly_
{
    int c; //系数 coefficient
    int e; //指数 exponent
}Poly;

int main()
{
    //用桶排序策略避免排序
    //乘积指数为正的桶，乘积指数为负的桶
    int multiBucketPos[MAX_E2]={0}, multiBucketNeg[MAX_E2]={0};
    //加法指数为正的桶，加法指数为负的桶
    int addBucketPos[MAX_E]={0}, addBucketNeg[MAX_E]={0};
    int n1, n2, e, c, i, j;
    //第一个多项式结构体数组
    Poly p1[MAX_E2];
    //第二个多项式结构体数组
    Poly p2[MAX_E2];
    int bFirst;

    //读入第一个多项式的总项数
    scanf("%d", &n1);
    //读入第一个多项式
    for(i=0; i<n1; ++i)
    {
        scanf("%d%d",&p1[i].c, &p1[i].e);
        //边读边做加法
        if(p1[i].e>=0)
            addBucketPos[p1[i].e]+=p1[i].c;
        else
            addBucketNeg[-p1[i].e]+=p1[i].c;
    }
    //读入第二个多项式的总项数
    scanf("%d", &n2);
    //读入第二个多项式
    for(i=0; i<n2; ++i)
    {
        scanf("%d%d",&p2[i].c, &p2[i].e);
        //边读边做加法
        if(p2[i].e>=0)
            addBucketPos[p2[i].e]+=p2[i].c;
        else
            addBucketNeg[-p2[i].e]+=p2[i].c;
    }
    //计算多项式乘法
    for(i=0; i<n1; ++i)
    {
        for(j=0; j<n2; ++j)
        {
            e = p1[i].e+p2[j].e;
            c = p1[i].c*p2[j].c;
            if(c!=0)
            {
                if(e>=0)
                    multiBucketPos[e]+=c;
                else
                    multiBucketNeg[-e]+=c;
            }
        }
    }


    //打印乘法的桶数据
    //正指数，反向打印
    bFirst = 1;
    for(i=MAX_E2-1; i>=0; --i)
    {
        //桶里得有东西
        if(multiBucketPos[i])
        {
            //不是本行的第一次打印则先打印一个空格
            if(!bFirst)
                printf(" ");
            printf("%d %d",multiBucketPos[i], i);
            bFirst = 0;
        }
    }
    //负指数，正向打印
    for(i=1; i<MAX_E; ++i)
    {
        //桶里得有东西
        if(multiBucketNeg[i])
        {
            //不是本行的第一次打印则先打印一个空格
            if(!bFirst)
                printf(" ");
            printf("%d %d", multiBucketNeg[i], -i);
            bFirst = 0;
        }
    }

    //零多项式
    if(bFirst)
        printf("0 0\n");
    else
        printf("\n");

    //打印加法的桶数据
    //正指数，反向打印
    bFirst = 1;
    for(i=MAX_E-1; i>=0; --i)
    {
        //桶里得有东西
        if(addBucketPos[i])
        {
            //不是本行的第一次打印则先打印一个空格
            if(!bFirst)
                printf(" ");
            printf("%d %d", addBucketPos[i], i);
            bFirst = 0;
        }
    }
    //负指数，正向打印
    for(i=1; i<MAX_E; ++i)
    {
        //桶里得有东西
        if(addBucketNeg[i])
        {
            //不是本行的第一次打印则先打印一个空格
            if(!bFirst)
                printf(" ");
            printf("%d %d", addBucketNeg[i],-i);
            bFirst = 0;
        }
    }
    //零多项式
    if(bFirst)
        printf("0 0\n");
    else
        printf("\n");
}
