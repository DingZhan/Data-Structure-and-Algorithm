#include <stdio.h>
#define MAX_N 101

int Reverse(int a[], int left, int right)
{
    int i, j, t;
    for(i=left, j=right; i<j; ++i, --j)
    {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

//根据循环左移后的位置信息，可以通过三次反转实现循环左移
//第一次反转整个数组
//第二次反转0至n-1-m位置的元素
//第三次反转n-1-m+1至n-1位置的元素
//m需要先取余保证小于n
int main()
{
    int n, m, i, a[MAX_N];
    scanf("%d%d", &n, &m);
    m%=n;
    for(i=0; i<n; ++i)
        scanf("%d", a+i);
    //第一次反转整个数组
    Reverse(a, 0, n-1);
    //第二次反转0至n-1-m位置的元素
    Reverse(a, 0, n-1-m);
    //第三次反转n-1-m+1至n-1位置的元素
    Reverse(a, n-1-m+1, n-1);
    for(i=0; i<n; ++i)
    {
        if(i!=0)
            printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}
