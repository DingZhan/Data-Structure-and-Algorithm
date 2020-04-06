#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 32
#define MAX_SIZE 32
#define ERROR -100000000
/*前缀表达式求值:
  要从右至左扫描表达式，如果是数字，则放到数据栈中；
  若为运算符，则从数据栈中弹出两个数据，进行计算，然后将计算结果再次压入数据栈；
  扫描到表达式最左端时扫描结束，最后数据栈中唯一的数据就是运算的最终结果。
*/
typedef struct Stack_
{
    double data[MAX_SIZE];
    int top;
}Stack;

Stack* CreateStack()
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}
void FreeStack(Stack**s)
{
    free(*s);
    *s = NULL;
}
int IsEmpty(Stack *s)
{
    return s->top == -1;
}

int IsFull(Stack *s)
{
    return s->top == MAX_SIZE-1;
}
int GetSize(Stack *s)
{
    return s->top+1;
}
int Push(Stack*s, double d)
{
    if(IsFull(s))
        return 0;
    s->data[++s->top] = d;
    return 1;
}

double Pop(Stack *s)
{
    if(IsEmpty(s))
        return ERROR;
    return s->data[s->top--];
}
double Top(Stack *s)
{
    if(IsEmpty(s))
        return ERROR;
    return s->data[s->top];
}
int main()
{
    //从一行字符串中提取的符号数组
    char tokens[MAX_N][MAX_N];
    //数据栈
    Stack *s = CreateStack();
    char lineStr[MAX_N], token[MAX_N];
    double data1, data2;
    int i, ntoken=0, pos=0, step;

    //得到一行字符串
    fgets(lineStr, MAX_N, stdin);
    //读取每个符号（字符串，以空格分隔）
    while(1)
    {
        //读取一个符号（字符串）, %n用来获得当前scanf走过的字符数
        if(sscanf(lineStr+pos, "%s%n", token, &step)!=1)
            break;
        if(strcmp(token, "\n")==0)
            break;
        pos+=step;
        //把读取的符号加入符号数组
        strcpy(tokens[ntoken++], token);
    }
    //从右至左解析符号
    for(i=ntoken-1; i>=0; --i)
    {
        //如果当前符号串是四则运算符，则需要从数据栈中弹出两个数据进行计算
        if(strlen(tokens[i])==1 &&(
           tokens[i][0]=='+'||
           tokens[i][0]=='-'||
           tokens[i][0]=='*'||
           tokens[i][0]=='/'))
        {
            //如果数据栈中没有两个数，则输入的是非法前缀表达式，清除堆栈然后退出循环
            if(GetSize(s)<2)
            {
                //error happened, so clear stack
                while(!IsEmpty(s))
                    Pop(s);
                break;
            }
            //从数据栈中弹出两个数据进行计算
            data1 = Pop(s);
            data2 = Pop(s);
            if(tokens[i][0]=='+')
                data1 = data1+data2;
            else if(tokens[i][0]=='-')
                data1 = data1-data2;
            else if(tokens[i][0]=='*')
                data1 = data1*data2;
            else if(tokens[i][0]=='/')
            {
                if(data2==0)
                {
                    //除零异常，有一个测试点，所以必须处理该异常
                    //清除堆栈然后退出循环
                    //error happened, so clear stack
                    while(!IsEmpty(s))
                        Pop(s);
                    break;
                }
                data1 = data1/data2;
            }
            //把计算的数据结果压回数据堆栈
            Push(s, data1);
            //继续下一次符号解析
            continue;
        }
        else
            //当前符号是数字，把该数字压入数据堆栈
            Push(s, atof(tokens[i]));
    }

    //如果最终数据堆栈中元素个数不为1，则说明是非法前缀表达式
    if(GetSize(s)!=1)
        printf("ERROR\n");
    else
        printf("%.1lf\n",Top(s));
    FreeStack(&s);
    return 0;
}
