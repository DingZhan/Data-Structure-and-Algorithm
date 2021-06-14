#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ERROR -100
#define MAXS 31
//扫描中缀表达式时候，返回的三种类型：操作数，操作符，结束符
typedef enum {num, opr, end} Type;

//堆栈数据结构和函数：中缀转后缀，堆栈里是操作符
typedef char ElementType;
typedef struct Stack_
{
    ElementType data[MAXS];
    int top;
}Stack;

Stack *CreateStack( void )
{
    Stack *S;
    S = (Stack*)calloc(1,sizeof(Stack));
    S->top = -1;
    
    return S;
}
bool IsFull( Stack *S )
{
    return S->top==MAXS-1?true:false;
}
bool IsEmpty( Stack *S )
{
    return S->top==-1?true:false;
}
void Push( Stack *S, ElementType X )
{
    if(IsFull(S) == true)
        return ;
    else
        S->data[++S->top] = X;
}
ElementType Pop( Stack *S )
{
    if(IsEmpty(S) == true)
        return ERROR;
    else
        return S->data[S->top--];
}
ElementType Top( Stack *S )
{
    if(IsEmpty(S) == true)
        return ERROR;
    else
        return S->data[S->top];
}
//sign_start表示用来是否将’-‘,'+'识别为操作数的符号位
//字符串起始扫描时或者字符串读到'('时候需要设置sign_start 为true
bool sign_start;

//比较两个字符的优先级，利用levels优先级数组进行比较，Compare返回为true表示op1优先级大于op2
bool Compare( char op1, char op2 )
{
    int i;
    int level1,level2;
    int levels[] = {2,2,3,3,1};
    char ops[] = {'+', '-', '*', '/', '('};
    
    for(i=0;ops[i] != op1;++i);
    level1 = levels[i];
    for(i=0;ops[i] != op2;++i);
    level2 = levels[i];
    
    return level1 > level2?true:false;
}

//从当前表达式起始位置start开始，扫描出一个操作数或操作符并存入str中
Type GetOp( char *expr, int *start, char *str)
{
    double f;
    int length;
    //如果遇到了字符串终结符，则扫描结束
    if(expr[(*start)] == '\0')
        return end;
    //如果是操作数，或者是带有符号位的操作数
    if((isdigit(expr[(*start)])) || (sign_start == true && (expr[(*start)] == '+' || expr[(*start)] == '-')))
    {
        //利用sscanf扫描出一个浮点数，%n用来得到当前sscanf操作行走的长度
        sscanf(expr+(*start), "%lf%n", &f, &length);
        //将该操作数copy到str中，这里只能用strncpy，不能用strcpy，想一想为什么？
        strncpy(str, expr+(*start), length);
        //别忘记在str后面补上'\0'
        str[length] = '\0';
        //将下一次扫描位置偏移length位
        (*start) += length;
        return num;
    }
    else//否则是操作符
    {
        str[0] = expr[(*start)];
        str[1] = '\0';
        //别忘记偏移一位
        (*start)++;
        return opr;
    }
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

//-25+3*(-0.7-4)+8/4
//2973+933*(0.7837-4)+8693/4
//-3.2-3*(-5.2+2.221)
//.5+3.2
//-3.2-3*(-5.2+2.221)+1.789

//特别注意：操组数的+号（正号）就不要加到后缀表达式中了，否则有一个测试点始终过不了
int main()
{
    int i;
    int flag = 0; //flag用来控制前置空格的输出
    
    Stack *S;
    Type type;
    
    char EXP[MAXS];
    char str[MAXS];
    
    sign_start = true;
    gets(EXP);
    S = CreateStack();
    i = 0;
    while(1)
    {
        //扫描一个操作数或操作符
        type = GetOp(EXP, &i, str);
        //如果是结束符则退出循环
        if(type == end)
            break;
        //如果是操作数则直接输出
        if(type == num)
        {
            if(flag != 0)
                printf(" ");
            //操作数的'+’号不输出
            if(str[0]=='+')
                printf("%s",str+1);
            else
                printf("%s",str);
            flag = 1;
            //当前是操作数，下一个肯定不能再是操作数
            sign_start = false;
        }
        else
        {
            if(str[0] == '(') //如果当前是左括号，则下一个一定是操作数，所以把符号标记位启动起来
                sign_start = true;
            else
                sign_start = false;
            //如果是左括号，则入栈
            if(str[0] == '(')
            {
                Push(S, '(');
            }
            //如果是右括号，则弹出堆栈，直到碰到第一个左括号
            else if(str[0] == ')')
            {
                while(1)
                {
                    char t = Pop(S);
                    if(t == '(')
                        break;
                    if(flag != 0)
                        printf(" ");
                    printf("%c",t);
                    flag = 1;
                }
            }
            else
            {
                //否则根据优先级是否入栈或者弹出栈
                while(1)
                {
                    //如果堆栈为空，则肯定入栈，并退出循环
                    if(IsEmpty(S) == true)
                    {
                        Push(S,str[0]);
                        break;
                    }
                    //如果新来的操作符优先级高，则入栈并退出循环
                    if(Compare(str[0], Top(S)) == true)
                    {
                        Push(S,str[0]);
                        break;
                    }
                    else //否则弹出栈顶元素
                    {
                        if(flag != 0)
                            printf(" ");
                        printf("%c",Pop(S));
                        flag = 1;
                    }
                }
            }
        }
    }
    //最后，如果堆栈还不为空，则弹出堆栈里所有操作符
    while(IsEmpty(S) != true)
    {
        if(flag != 0)
            printf(" ");
        printf("%c",Pop(S));
        flag = 1;
    }
    printf("\n");
    //别忘记释放内存
    free(S);
    return 0;
}
