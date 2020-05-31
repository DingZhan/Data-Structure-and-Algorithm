#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//hash表长度，一个质数
#define MAX_N 100003
//定义错误码
#define ERROR -1

//得到下一个质数
int NextPrime(int n)
{
    int p = (n%2)?(n+2):(n+1);
    int i;
    while(1)
    {
        for(i=sqrt(p); i>2; --i)
        {
            if(p%i==0)
                break;
        }
        if(i==2)
            break;
        p+=2;
    }
    return p;
}

//hash表链式表示方法的链表结点结构体
typedef struct Node_
{
    //身份证
    char ID[19];
    //总公里数
    long long miles;
    //next指针
    struct Node_ *next;
}Node;

//hash表结构体
typedef struct HashTable_
{
    //链表头动态数组
    Node* heads;
    //hash表表长度，hash函数的大质数
    int size;
}HashTable;

//创建hash表
HashTable* CreateHashTable(int size)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    //分配hash表链式表示的头结点数组，用calloc把结点所有内容清空为0
    hashTable->heads = (Node*)calloc(size, sizeof(Node));
    return hashTable;
}

//hash函数，字符串移位方法
int Hash(HashTable *hashTable, char ID[19])
{
   long long v = 0;
   int i;
   for(i=8; i<18; ++i)
       v=v*10+(ID[i]-'0');
   if(ID[18]=='X'||ID[18]=='x')
        v = v*10+10;
   else
       v=v*10+(ID[18]-'0');
   return v%hashTable->size;
}

//hash表里查找关键字
Node* Find(HashTable *hashTable, char ID[19])
{
    //得到关键字映射的位置
    int pos = Hash(hashTable, ID);
    //遍历带头结点的链表，查找该关键字是否出现过
    Node *node = hashTable->heads[pos].next;
    while(node)
    {
        //该关键字出现过
        if(!strcmp(node->ID, ID))
            break;
        node = node->next;
    }
    return node;
}

//向hash表里插入一个关键字
void AddRecord(HashTable *hashTable, char ID[19], int miles)
{
    //查找该关键字是否出现过
    Node *node = Find(hashTable, ID);
    //出现过，则直接累加旅程公里数
    if(node)
    {
        node->miles+=miles;
        return;
    }
    //该关键字没出现过，则创建新结点并加入链表头
    int pos = Hash(hashTable, ID);
    node = (Node*)malloc(sizeof(Node));
    node->miles = miles;
    strcpy(node->ID, ID);
    node->next = hashTable->heads[pos].next;
    hashTable->heads[pos].next = node;
    return;
}

//释放hash表
void FreeHashTable(HashTable* hashTable)
{
    //释放所有链表头
    free(hashTable->heads);
    //释放表
    free(hashTable);
}

int main()
{
    int N, K, i, miles, M;
    char ID[19];
    //创建hash表
    HashTable *hashTable = CreateHashTable(MAX_N);
    Node *node;

    //读入N条飞行记录和最短旅程K
    scanf("%d%d", &N, &K);
    for(i=0; i<N; ++i)
    {
        //读入身份证和公里数
        scanf("%s%d", ID, &miles);
        //最小阈值
        if(miles<K)
            miles = K;
        //添加记录
        AddRecord(hashTable, ID, miles);
    }
    //读入查询次数M
    scanf("%d", &M);
    //查询M次
    for(i=0; i<M; ++i)
    {
        scanf("%s", ID);
        //查询旅行记录
        node = Find(hashTable, ID);
        if(!node)
            printf("No Info\n");
        else
            printf("%d\n", node->miles);
    }

    //释放hash表
    FreeHashTable(hashTable);
    return 0;
}
