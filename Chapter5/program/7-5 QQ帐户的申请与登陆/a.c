#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 200003
#define MAX_N 100001
#define MAX_PASS_LEN 17

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

typedef struct Node_
{
    long long id;
    char pass[MAX_PASS_LEN];
    struct Node_ *next;
}Node;

typedef struct HashTable_
{
    Node *nodes;
    int size;
}HashTable;

HashTable* CreateHashTable(int size)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->nodes = (Node*)calloc(size, sizeof(Node));
    return hashTable;
}

int Hash(long long id, HashTable* hashTable)
{
    return (int)(id%hashTable->size);
}
typedef enum LOGIN_STATE_ {LS_OK, LS_WRONG_PASS, LS_NOT_EXIST}LOGIN_STATE;

//1 Login: OK; 2 ERROR: Wrong PW; 3 ERROR: Not Exist
LOGIN_STATE Find(HashTable *hashTable, long long id, const char* pass)
{
    int pos = Hash(id, hashTable);
    Node* node = hashTable->nodes[pos].next;
    while(node)
    {
        if(node->id==id && !strcmp(node->pass, pass))
            return LS_OK;
        else if(node->id==id)
            return LS_WRONG_PASS;
        node = node->next;
    }
    return LS_NOT_EXIST;
}

//0 ERROR: Exist,  1 New: OK
int Insert(HashTable *hashTable, long long id, const char* pass)
{
    LOGIN_STATE ls = Find(hashTable, id, pass);
    if(ls!=LS_NOT_EXIST)
        return 0;
    int pos = Hash(id, hashTable);
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    strcpy(node->pass, pass);
    node->next = hashTable->nodes[pos].next;
    hashTable->nodes[pos].next = node;
    return 1;
}

void FreeHashTable(HashTable *hashTable)
{
    free(hashTable->nodes);
    free(hashTable);
}

int main()
{
    int i, N, ret;
    char code[2], pass[MAX_PASS_LEN];
    long long id;
    LOGIN_STATE ls;

    HashTable *hashTable = CreateHashTable(MAX_SIZE);
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        scanf("%s %lld %s", code, &id, pass);
        if(code[0]=='L')
        {
            ls= Find(hashTable, id, pass);
            if(ls==LS_OK)
                printf("Login: OK\n");
            else if(ls==LS_WRONG_PASS)
                printf("ERROR: Wrong PW\n");
            else
                printf("ERROR: Not Exist\n");
        }
        else
        {
            ret= Insert(hashTable, id, pass);
            if(ret==0)
                printf("ERROR: Exist\n");
            else
                printf("New: OK\n");
        }
    }
    FreeHashTable(hashTable);
    return 0;
}
