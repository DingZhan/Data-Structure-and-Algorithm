#include <stdio.h>

#define MAX_N 31

//贪心+回溯
//思想：贪心：将当前n加入到当前组合中
//回溯：当前n不在当前组合中


void Combination(int n, int r, int *solutions, int data[], int size)
{
    int i;
    //如果已经找到了所期望的所有组合
    if((*solutions)==0)
        return;
    //找到了一组完整的组合数
    if(r==0)
    {
        //打印当前组合结果
        for(i=0; i<size; ++i)
        {
            //if(i!=0)
                printf(" ");
            printf("%d", data[i]);
        }
        printf("\n");
        //把期望的方案结果减少1
        --(*solutions);
        return;
    }
    //如果当前n为0，则没法再组合
    if(n<=0)
        return;
    //贪心：把当前n加入到组合中
    data[size++] = n;
    //当前n在组合中，则需要从n-1个数中选取r-1个数
    Combination(n-1, r-1, solutions, data, size);
    //回溯：当前n不在组合中
    --size;
    //当前n不在组合中，则需要从n-1个数中选取r个数
    Combination(n-1, r, solutions, data, size);
}

int main()
{
    int n, r, t, data[MAX_N];
    scanf("%d%d%d", &n, &r, &t);
    Combination(n, r, &t, data, 0);
    return 0;
}


