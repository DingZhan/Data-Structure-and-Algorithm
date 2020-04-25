#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001

//并查集
int parents[MAX_N];
int FindRoot(int i)
{
    while(parents[i]>0)
        i = parents[i];
    return i;
}
//按秩合并：按照小集合合并到大集合的原则合并
//一定要按秩合并：普通合并会有一个测试点超时
int Union(int c1, int c2)
{
    int r1 = FindRoot(c1);
    int r2 = FindRoot(c2);
    if(r1==r2)
      return r1;
    //r2集合元素多，则r1合并到r2上去
    if(parents[r2]<parents[r1])
    {
        //修改r2集合元素个数
        parents[r2]+=parents[r1];
        parents[r1] = r2;
    }
    else //r1集合元素多，则r2合并到r1上去
    {
        //修改r1集合元素个数
        parents[r1]+=parents[r2];
        parents[r2] = r1;
    }
    return r1;
}

int SameTree(int c1, int c2)
{
    int r1 = FindRoot(c1);
    int r2 = FindRoot(c2);
    return r1==r2;
}

int main()
{
    int N, c1, c2, i, root;
    char token;
    scanf("%d", &N);
    //初始化并查集为-1,表示所有元素都是独立的集合
    for(i=1; i<=N; ++i)
        parents[i] = -1;
    while(1)
    {
        scanf("%c", &token);
        if(token=='S')
            break;
        if(token=='I')
        {
            scanf("%d%d", &c1, &c2);
            Union(c1, c2);
        }
        else if(token=='C')
        {
            scanf("%d%d", &c1, &c2);
            if(SameTree(c1, c2))
                printf("yes\n");
            else
                printf("no\n");
        }
    }
    //统计集合数目
    int count=0;
    for(i=1; i<=N; ++i)
    {
        if(parents[i] < 0)
            ++count;
    }
    if(count==1)
        printf("The network is connected.\n", count);
    else
        printf("There are %d components.\n", count);
    return 0;
}

