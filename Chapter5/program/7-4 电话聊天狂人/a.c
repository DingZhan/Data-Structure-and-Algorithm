#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100001

int NextPrime(int p)
{
    int i;
    p = (p%2)?(p+2):(p+1);
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

typedef struct Node_
{
    long long phoneNum;
    int count;
    struct Node_ *next;
}Node;

typedef struct HashTable_
{
    Node* heads;
    int size;
}HashTable;

HashTable* CreateHashTable(int size)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->heads = (Node*)calloc(size, sizeof(Node));
    return hashTable;
}

void DeleteHashTable(HashTable *hashTable)
{
    int i;
    Node *node, *t;
    for(i=0; i<hashTable->size; ++i)
    {
        node = hashTable->heads[i].next;
        while(node)
        {
            t = node->next;
            free(node);
            node = t;
        }
    }
    free(hashTable->heads);
    free(hashTable);
}

int Hash(long long phoneNum, int tableSize)
{
    return (int)((phoneNum%10000000)%tableSize);
}

Node* Find(HashTable *hashTable, long long phoneNum)
{
    int pos = Hash(phoneNum, hashTable->size);
    Node* p = hashTable->heads[pos].next;
    while(p)
    {
        if(p->phoneNum==phoneNum)
            return p;
        p = p->next;
    }
    return p;
}

Node* Insert(HashTable *hashTable, long long phoneNum)
{
    Node* p = Find(hashTable, phoneNum);
    if(p)
    {
        ++p->count;
        return p;
    }
    int pos = Hash(phoneNum, hashTable->size);
    p = (Node*)calloc(1, sizeof(Node));
    p->phoneNum = phoneNum;
    p->next = hashTable->heads[pos].next;
    p->count = 1;
    hashTable->heads[pos].next = p;
    return p;
}

void PrintCrazyMan(HashTable *hashTable)
{
    int i, crazyCount=0, sameCrazyNum=1;
    long long crazyPhoneNum = 99999999999;
    Node *node;
    for(i=0; i<hashTable->size; ++i)
    {
        node = hashTable->heads[i].next;
        while(node)
        {
            if(node->count>crazyCount)
            {
                crazyCount = node->count;
                crazyPhoneNum = node->phoneNum;
                sameCrazyNum = 1;
            }
            else if(node->count==crazyCount)
            {
                if(node->phoneNum<crazyPhoneNum)
                    crazyPhoneNum = node->phoneNum;
                ++sameCrazyNum;
            }
            node = node->next;
        }
    }
    if(sameCrazyNum==1)
    {
        printf("%lld %d", crazyPhoneNum, crazyCount);
    }
    else if(sameCrazyNum>1)
    {
        printf("%lld %d %d", crazyPhoneNum, crazyCount, sameCrazyNum);
    }
}

int main()
{
    int i, N, size;
    long long phoneNum1, phoneNum2;
    HashTable *hashTable;

    scanf("%d", &N);
    size = NextPrime(N);
    hashTable = CreateHashTable(size);
    for(i=0; i<N; ++i)
    {
        scanf("%lld%lld", &phoneNum1, &phoneNum2);
        Insert(hashTable, phoneNum1);
        Insert(hashTable, phoneNum2);
    }
    PrintCrazyMan(hashTable);
    DeleteHashTable(hashTable);

    return 0;
}
