#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10002
#define ERROR -1

int NextPrime(int size)
{
    int p, i;
    if(size<=2)
        return 2;
    p = (size%2)?size:(size+1);
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

typedef enum State_{EMPTY=0, TAKEN}State;
typedef struct Cell_
{
    int data;
    State state;
}Cell;
typedef struct HashTable_
{
    Cell *cells;
    int size;
}HashTable;

HashTable * CreateHashTabel(int size)
{
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->cells = (Cell*)calloc(size, sizeof(Cell));
    return table;
}
void DeleteHashTable(HashTable *table)
{
    free(table->cells);
    free(table);
}
int Insert(HashTable* table, int data)
{
    int pos = data%table->size;
    if(table->cells[pos].state==EMPTY)
    {
        table->cells[pos].data = data;
        table->cells[pos].state = TAKEN;
        return pos;
    }
    int i, newPos;
    for(i=1; i<table->size; ++i)
    {
        newPos = (pos+i*i)%table->size;
        if(table->cells[newPos].state==EMPTY)
        {
            table->cells[newPos].data = data;
            table->cells[newPos].state = TAKEN;
            return newPos;
        }
    }
    return ERROR;
}

int main()
{
    int size, N, i, data, pos[MAX_N];
    HashTable *hashTable;

    scanf("%d%d", &size, &N);
    size = NextPrime(size);
    hashTable = CreateHashTabel(size);
    for(i=0; i<N; ++i)
    {
        scanf("%d", &data);
        pos[i] = Insert(hashTable, data);
    }
    for(i=0; i<N; ++i)
    {
        if(i)
            printf(" ");
        if(pos[i]!=ERROR)
            printf("%d", pos[i]);
        else
            printf("-");
    }

    return 0;
}
