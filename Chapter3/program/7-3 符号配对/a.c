#include <stdio.h>

#define MAX_N 202

//堆栈结构体
typedef struct Stack_
{
    char data[MAX_N];
    int top;
}Stack;
//初始化堆栈
void Init(Stack *s)
{
    s->top = -1;
}
//压栈
void Push(Stack *s, char c)
{
    s->data[++s->top] = c;
}
//出栈，栈为空时返回'\0'
char Pop(Stack *s)
{
    if(s->top==-1)
        return '\0';
    return s->data[s->top--];
}
//返回栈顶元素，栈为空时返回'\0'
char Top(Stack *s)
{
    if(s->top==-1)
        return '\0';
    return s->data[s->top];
}
//判断堆栈是否为空
int IsEmpty(Stack *s)
{
    return s->top==-1;
}

//左注释符"/*"占两个字符，所以在堆栈保存中我们可以直接使用"/"代替"/*"
int main()
{
    char c, lastc='\0';
    Stack s;
    int bSucc=1;

    //初始化堆栈为空
    Init(&s);
    while(1)
    {
        c = getchar();
        //如果当前字符为换行符，上一个字符为'.',则表示解析结束
        if(c=='\n' && lastc=='.')
            break;
        //如果当前字符为'*',上一个字符为'/'，则表示解析到左注释符号
        if(c=='*' && lastc=='/')
        {
            //把左注释符压栈
            Push(&s, '/');
            //避免后续可能的"*/"使用当前的"*"，将当前字符变成'\0'
            c = '\0';
        }
        //如果是左括号，压栈
        else if(c=='(' || c=='[' || c=='{')
            Push(&s, c);
        //如果出现的是右注释符号
        else if(c=='/' && lastc=='*')
        {
            //如果堆栈为空，则表示没匹配到左注释符
            if(IsEmpty(&s))
            {
                bSucc=0;
                break;
            }
            //栈顶不是左注释符号，则表示不匹配
            if(Top(&s)!='/')
            {
                bSucc=0;
                break;
            }
            //成功匹配，弹出栈顶的左注释符
            Pop(&s);
            //为了避免后续的"/*"使用当前的'/'
            c = '\0';
        }
        //如果是右括号
        else if(c==')' || c==']' || c=='}')
        {
            //如果堆栈为空，则没法匹配到左括号
            if(IsEmpty(&s))
            {
                bSucc=0;
                break;
            }
            if(c==')')
            {
                if(Top(&s)!='(')
                {
                    bSucc=0;
                    break;
                }
            }
            else if(c=='}')
            {
                if(Top(&s)!='{')
                {
                    bSucc=0;
                    break;
                }
            }
            else if(c==']')
            {
                if(Top(&s)!='[')
                {
                    bSucc=0;
                    break;
                }
            }
            //成功匹配，则弹出匹配的左括号
            Pop(&s);
        }

        lastc = c;
    }
    //如果没发现不匹配的情况，则还需要检测堆栈是否为空，
    //如果非空，则表示还有左括号或者左注释符没有匹配
    if(bSucc)
    {
        if(!IsEmpty(&s))
            bSucc=0;
    }
    if(bSucc)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
        //堆栈为空一定是缺左括号
        if(IsEmpty(&s))
        {
            if(c=='/')
                printf("?-*/\n");
            else
                printf("?-%c\n", c);
        }
        else //缺右括号，找到堆顶元素，推测缺失的右符号
        {
            c = Pop(&s);
            if(c=='/')
                printf("/*-?\n");
            else
                printf("%c-?\n", c);
        }
    }
//    system("pause");
    return 0;
}
