#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 2048
#define ERROR -1


typedef struct Stack_
{
    char array[MAX_LEN];
    int top;
}Stack;

void Init(Stack *stack)
{
    stack->top = -1;
}
void Push(Stack *stack, char d)
{
    stack->array[++stack->top] = d;
}
char Pop(Stack *stack)
{
   if(stack->top==-1)
        return ERROR;
   return stack->array[stack->top--];
}
char Top(Stack *stack)
{
   if(stack->top==-1)
        return ERROR;
   return stack->array[stack->top];
}
int IsEmpty(Stack *stack)
{
   return stack->top==-1;
}
void PrintStack(Stack *stack)
{
    int i;
    for(i=stack->top; i>=0; --i)
        printf("%c ", stack->array[i]);
    printf("\n");
}

//原题的除法符号是错误的
int IsOperator(char c)
{
    char ops[] = {'+','-','*','/','('};
    int i;
    for(i=0; i<sizeof(ops)/sizeof(ops[0]); ++i)
    {
        if(c==ops[i])
            return 1;
    }
    return 0;
}

//测试op2优先级是否高于op1
//原题的除法符号是错误的
int IsHigherPriority(char op1, char op2)
{
    char ops[] = {'+','-','*','/','('};
    int orders[] = {1,1,2,2,0};
    int i, order1, order2;
    for(i=0; i<sizeof(ops)/sizeof(ops[0]); ++i)
    {
        if(op1==ops[i])
            order1 = orders[i];
        if(op2==ops[i])
            order2 = orders[i];
    }
    return order2>order1;
}

//具体算法，参考MOOC(数据结构-何钦明，陈越) 线性结构-堆栈
/*从头到尾读取中缀表达式的每个对象，对不同对象按不同情况处理。
1.运算数：直接输出
2.左括号：压入堆栈
3.右括号: 将栈顶的运算符弹出并输出，直到遇到左括号(出栈，不输出)
4.运算符:
  :若优先级大于栈顶运算符时，则把它压栈；
  :若优先级小于等于栈顶运算符时，将栈顶运算符弹出并输出；再比较新的栈顶运算符，
  直到该运算符大于栈顶运算符优先级为止，然后将该运算符压栈；
5.若各对象处理完毕，则把堆栈中存留的运算符一并输出。
*/
//-3+4第一个-不是减号，而应该当作数字一部分
//另外，+号（正号）就不要加到后缀中了，否则有一个测试点始终过不了
//例如5*(+3-2),  +3+5-6
void InfixToPostfix(const char*infix, char *postfix)
{
    char data[MAX_LEN], c, temp[2]={'\0'};
    int bLastData, i, bPostfixEmpty=1;
    Stack *s = (Stack*)malloc(sizeof(Stack));
    Init(s);

    postfix[0] = '\0';
    bLastData = 0;
    for(i = 0; infix[i]!='\0'; ++i)
    {
        if(infix[i]=='(')
        {
            bLastData = 0;
            Push(s, infix[i]);
        }
        else if(infix[i]==')')
        {
            bLastData = 0;
            while(1)
            {
                c = Pop(s);
                if(c=='(')
                    break;
                if(!bPostfixEmpty)
                    strcat(postfix, " ");
                temp[0] = c;
                strcat(postfix, temp);
                bPostfixEmpty = 0;
            }
        }
        //避免负号，正号当减号和加号,例如-3+5, (-3+2)
        //+3*(+3-5)
        else if((infix[i]=='+'||infix[i]=='-') &&
                (i==0 || infix[i-1]=='('))
        {
            //+号（正号）就不要加到后缀中了，否则有一个测试点始终过不了
            if(infix[i]=='-')
            {
                if(!bPostfixEmpty)
                    strcat(postfix, " ");
                temp[0] = infix[i];
                strcat(postfix, temp);
                bPostfixEmpty = 0;
                //-后面的数字之前不需要打印一个空格，因为这里已经打印过了
                bLastData = 1;
            }
            else
            {
                //+后面的数字之前需要打印一个空格
                bLastData = 0;
            }
        }
        else if(!bPostfixEmpty && IsOperator(infix[i]))
        {
            bLastData = 0;
            while(1)
            {
                if(IsEmpty(s) || IsHigherPriority(Top(s), infix[i]))
                {
                    Push(s, infix[i]);
                    break;
                }
                c = Pop(s);
                strcat(postfix, " ");
                temp[0] = c;
                strcat(postfix, temp);
                bPostfixEmpty = 0;
            }
        }
        //如果有空格，也能处理
        else if(infix[i]==' ')
        {
            bLastData = 0;
        }
        else
        {
            //不要加空格，因为和上一次的数字是同一个数据
            if(bLastData)
            {
                temp[0] = infix[i];
                strcat(postfix, temp);
                bPostfixEmpty = 0;
            }
            else
            {
                if(!bPostfixEmpty)
                    strcat(postfix, " ");
                temp[0] = infix[i];
                strcat(postfix, temp);
                bPostfixEmpty = 0;
            }
            bLastData = 1;
        }
    }

    while(!IsEmpty(s))
    {
        c = Pop(s);
        if(!bPostfixEmpty)
            strcat(postfix, " ");
        temp[0] = c;
        strcat(postfix, temp);
        bPostfixEmpty = 0;
    }

    free(s);
}

int main()
{
    char infix[MAX_LEN], postfix[MAX_LEN];
    gets(infix);
    InfixToPostfix(infix, postfix);
    puts(postfix);
    return 0;
}
