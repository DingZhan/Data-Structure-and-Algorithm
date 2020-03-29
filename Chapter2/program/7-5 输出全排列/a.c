#include <stdio.h>

#define MAX_N 10

//begin是待排列元素位置，当begin达到数组的最大下标时，一个排列结果就出来了。
//data是数组中所有元素，n是数组大小
void Permutation(int n, int data[], int begin)
{
    int i, t;
    //begin达到数组最大下标，打印一个排列结果
    if(begin==n-1)
    {
        for(i=0; i<n; ++i)
        {
            if(i!=0)
                printf(" ");
            printf("%d", data[i]);
        }
        printf("\n");
        return;
    }
    //把每一个数字挑出来放在最左边，递归调用结束后再还原回原来位置
    for(i=begin; i<n; ++i)
    {
        //贪心：将当前data[i]交换到最前面的data[begin]
        t = data[begin];
        data[begin] = data[i];
        data[i] = t;
        //递归排列下一个元素，待排列位置是begin+1
        Permutation(n, data, begin+1);
        //回溯：将data[i]和data[begin]再交换回来
        t = data[begin];
        data[begin] = data[i];
        data[i] = t;
    }
}

//为了保持字典序，通过右移的方式递归排列
void Permutation2(int n, int data[], int begin)
{
    int i, j, t;
    //begin达到数组最大下标，打印一个排列结果
    if(begin==n-1)
    {
        for(i=0; i<n; ++i)
            printf("%d", data[i]);
        printf("\n");
        return;
    }
    //把每一个数字挑出来放在最左边，递归调用结束后再还原回原来位置
    for(i=begin; i<n; ++i)
    {
        //贪心：将当前data[i]交换到最前面的data[begin], [begin,i)之间的右移
        t = data[i];
        for(j=i; j>begin; --j)
            data[j] = data[j-1];
        data[begin] = t;
        //递归排列下一个元素，待排列位置是begin+1
        Permutation2(n, data, begin+1);
        //回溯：将当前data[i]交换回最前面的data[begin], (begin,i]之间的左移
        t = data[begin];
        for(j=begin; j<i; ++j)
            data[j] = data[j+1];
        data[i] = t;
    }
}

int main()
{
    int n, data[MAX_N], i;
    scanf("%d", &n);
    for(i=0; i<n; ++i)
        data[i] = i+1;
    Permutation2(n, data, 0);
    return 0;
}
