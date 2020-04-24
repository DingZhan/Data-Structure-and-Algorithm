#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define INVALID_DATA -100000000
typedef struct Stack_
{
    int data[MAX_N];
    int top;
    int capacity;
}Stack;

//M是堆栈最大容量
Stack *CreateStack(int M)
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->capacity = M;
    s->top = -1;
    return s;
}
//清空堆栈
void Empty(Stack *s)
{
    s->top = -1;
}
//堆栈是否空
int IsEmpty(Stack *s)
{
    return s->top == -1;
}
//堆栈是否满
int IsFull(Stack *s)
{
    return s->top==s->capacity-1;
}
//压入元素到堆栈
int Push(Stack *s, int d)
{
    if(IsFull(s))
        return 0;
    s->data[++s->top] = d;
    return 1;
}
//弹出元素
int Pop(Stack* s)
{
    if(IsEmpty(s))
        return INVALID_DATA;
    return s->data[s->top--];
}
//返回栈顶元素
int Top(Stack *s)
{
    if(IsEmpty(s))
        return INVALID_DATA;
    return s->data[s->top];
}
//释放堆栈
void FreeStack(Stack*s)
{
    free(s);
}
int main()
{
    int M, N, K, i, j, cur, d;
    //验证序列
    int data[MAX_N];
    Stack *s;

    scanf("%d%d%d", &M, &N, &K);
    //创建一个堆栈
    s = CreateStack(M);
    for(j=0; j<K; ++j)
    {
        //读入一组序列
        for(i=0; i<N; ++i)
            scanf("%d", data+i);
        //设置待验证的序列初始下标
        i=0;
        //清空堆栈
        Empty(s);
        //当前待压入堆栈的元素值
        cur = 1;
        //当前待压入堆栈的元素值不大于N时
        while(cur<=N)
        {
            //如果堆栈为空，肯定要把当前值压入堆栈
            if(IsEmpty(s))
            {
                //压入当前值，如果堆栈满一定要退出循环
                if(!Push(s, cur++))
                    break;
                continue;
            }
            //如果栈顶元素值和当前序列的值相同，则弹出一个元素
            if(Top(s)==data[i])
            {
                //弹出一个元素
                Pop(s);
                //移动验证序列的下标
                ++i;
            }
            else
            {
                //否则压入当前元素，如果堆栈满一定要退出循环
                if(!Push(s, cur++))
                    break;
            }
        }

        //后续验证堆栈中剩下的元素是否和序列剩下的元素完全相同
        for(;i<N; ++i)
        {
            //如果序列还未验证完，但堆栈已空，则NO
            if(IsEmpty(s))
                break;
            //如果栈顶元素和当前序列元素不同，则NO
            if(Pop(s)!=data[i])
                break;
        }
        //如果堆栈不为空或者序列不结束，则NO
        if(i!=N || !IsEmpty(s))
            printf("NO\n");
        else
            printf("YES\n");
    }
    //释放堆栈内存
    FreeStack(s);

    return 0;
}
