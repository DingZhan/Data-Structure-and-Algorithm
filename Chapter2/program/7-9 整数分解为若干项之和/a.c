#include <stdio.h>

#define MAX_N 30

//贪心+回溯的递归算法


//rawN表示原始N的大小，numSolutions表示总的方案数目
//N表示当前待分解值，current表示当前分解的起始值
//data是方案保存的数组，size是数组中分解值个数
void Decompose(int rawN, int *numSolutions, int N, int current, int data[], int* size)
{
    int i;
    //如果当前值为0，表示已分解完毕
    if(N==0)
    {
        //前置打印封号
        if((*numSolutions)%4!=0)
            printf(";");
        //打印原始值
        printf("%d=", rawN);
        //打印分解结果
        for(i=0; i<(*size); ++i)
        {
            if(i!=0)
                printf("+");
            printf("%d", data[i]);
        }
        //累加方案数
        ++(*numSolutions);
        //如果方案数为4倍数，打印回车
        if((*numSolutions)%4==0)
            printf("\n");
        return;
    }
    for(i=current; i<=N; ++i)
    {
        //贪心，先把i作为分解值，加到结果数组中
        data[*size] = i;
        ++(*size);
        //因为N已经被i分解了，所以需要N-i，current为i
        Decompose(rawN, numSolutions, N-i, i, data, size);
        //回溯
        --(*size);
    }
}

int main()
{
    int N, numSolutions=0, data[MAX_N], size=0;

    scanf("%d", &N);

    Decompose(N, &numSolutions, N, 1, data, &size);

    //如果方案数不为4的倍数加个回车
    if(numSolutions%4!=0)
        printf("\n");
    return 0;
}


