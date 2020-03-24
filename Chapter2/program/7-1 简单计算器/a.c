#include <stdio.h>

int main()
{
    char op;
    int left, right;

    //先读取左边的操作数
    if(scanf("%d", &left)!=1)
    {
        printf("ERROR\n");
        return 0;
    }

    while(1)
    {
        //读取操纵符
        if(scanf("%c", &op)!=1)
        {
            printf("ERROR\n");
            return 0;
        }
        //如果是等号则退出循环
        if(op=='=')
            break;
        //读取右边的操作数
        if(scanf("%d", &right)!=1)
        {
            printf("ERROR\n");
            return 0;
        }
        if(op=='+')
            left+=right;
        else if(op=='-')
            left-=right;
        else if(op=='*')
            left*=right;
        else if(op=='/')
        {
            if(right==0)
            {
                printf("ERROR\n");
                return 0;
            }
            left/=right;
        }
        else
        {
            printf("ERROR\n");
            return 0;
        }
    }
    printf("%d\n", left);
    return 0;
}
