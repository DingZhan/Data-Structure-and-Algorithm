#include <stdio.h>

//堆栈结构体
typedef struct Stack_
{
    int n;
    int top;
}Stack;

//初始化堆栈，初始化栈顶位置和栈最大容量
void Init(Stack *s, int n)
{
    s->n = n;
    s->top = -1;
}
//压栈,栈满时候返回0
int Push(Stack *s)
{
    if(s->top>=s->n-1)
        return 0;
    ++s->top;
    return 1;
}

//出栈，栈为空时返回0
int Pop(Stack *s)
{
    if(s->top==-1)
        return 0;
    --s->top;
    return 1;
}

//判断堆栈是否为空
int IsEmpty(Stack *s)
{
    return s->top==-1;
}

#define MAX_LEN 101
int main()
{
    Stack stack;
    int i, N, M, bSucc;
    char str[MAX_LEN], *p;
    scanf("%d%d", &N, &M);
    gets(str);
    for(i=0; i<N; ++i)
    {
        Init(&stack, M);
        gets(str);
        bSucc=1;
        for(p = str; (*p)!='\0'; ++p)
        {
            if((*p)=='S')
            {
                if(!Push(&stack))
                {
                    bSucc=0;
                    break;
                }
            }
            else
            {
                if(!Pop(&stack))
                {
                    bSucc=0;
                    break;
                }
            }
        }
        //最后还要检查堆栈是否非空，非空的堆栈也属于错误操作
        if(bSucc)
        {
            if(!IsEmpty(&stack))
                bSucc=0;
        }
        if(bSucc)
            printf("YES\n");
        else
            printf("NO\n");
    }
//    system("pause");
    return 0;
}
