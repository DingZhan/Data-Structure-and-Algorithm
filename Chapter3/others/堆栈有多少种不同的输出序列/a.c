#include <stdio.h>

#define MAX_SIZE 5
#define ERROR -1

typedef struct Stack_
{
    int array[MAX_SIZE];
    int top;
}Stack;

void Init(Stack *stack)
{
    stack->top = -1;
}
void Push(Stack *stack, int d)
{
    stack->array[++stack->top] = d;
}
int Pop(Stack *stack)
{
   if(stack->top==-1)
        return ERROR;
   return stack->array[stack->top--];
}
int IsEmpty(Stack *stack)
{
   return stack->top==-1;
}
void PrintStack(Stack *stack)
{
    int i;
    for(i=stack->top; i>=0; --i)
        printf("%d ", stack->array[i]);
    printf("\n");
}
void PrintStack2(Stack *stack)
{
    int v;
    while((v=Pop(stack))!=ERROR)
        printf("%d ", v);
    printf("\n");
}

void ListAllStack(int data[], int n, int pos, Stack* stack, int result[], int rn)
{
    int v, i;
    if(pos==n)
    {
        for(i=0; i<rn; ++i)
            printf("%d ", result[i]);
        PrintStack(stack);
//        while((v=Pop(stack))!=ERROR)
//            printf("%d ", v);
        printf("\n");
//        PrintStack(stack);
        return;
    }
    //要么把当前数据压到堆栈，要么从堆栈里退栈一个元素
    Push(stack, data[pos]);
    ListAllStack(data, n, pos+1, stack, result, rn);
    Pop(stack);

//    while(!IsEmpty(stack))
    {
        v = Pop(stack);
        if(v!=ERROR)
        {
            result[rn++] = v;
            ListAllStack(data, n, pos, stack, result, rn);
        }
    }
}

int main()
{
    Stack stack;
    int data[MAX_SIZE], i, result[MAX_SIZE];
    for(i=0; i<MAX_SIZE; ++i)
        data[i] = i+1;
    Init(&stack);
    ListAllStack(data, MAX_SIZE, 0, &stack, result, 0);
    return 0;
}
