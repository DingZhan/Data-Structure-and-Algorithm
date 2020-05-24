#include <stdio.h>
#include <stdlib.h>

//最大数据量
#define MAX_N 1001
//插入失败返回值
#define ERROR -1

//单元状态：空，已存数据（实际还有被删除）
typedef enum EntryType_ {EMPTY=0, LEGITIMATE} EntryType;

//定义单元格结构体
typedef struct Cell_
{
    //数据值，也是关键字
    int key;
    //单元格状态
    EntryType type;
}Cell;

//定义Hash表结构体
typedef struct HashTable_
{
    //单元格数组
    Cell *data;
    //最大质数，也是单元格数组大小
    int maxSize;
}HashTable;

//创建Hash表
HashTable* CreateHashTable(int tableSize)
{
    //分配Hash表内存
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    //设置Hash表大小
    table->maxSize = tableSize;
    //分配Hash表单元格数组内存，这里用calloc是要把状态设置成EMPTY(0)
    table->data = (Cell*)calloc(sizeof(Cell), tableSize);
    return table;
}

//将关键字插入Hash表
int Insert(HashTable* hashTable, int key)
{
    //除留余数Hash函数得到关键字插入位置
    int pos = key%hashTable->maxSize;
    //如果该位置为空，则插入该位置
    if(hashTable->data[pos].type==EMPTY)
    {
        hashTable->data[pos].key = key;
        //设置占据标记
        hashTable->data[pos].type=LEGITIMATE;
        return pos;
    }
    //如果该位置不为空，但是值正好是关键字Key，则直接返回
    if(hashTable->data[pos].type==LEGITIMATE && hashTable->data[pos].key==key )
        return pos;
    //冲突的线性探测
    int i, curPos;
    for(i=1; i<hashTable->maxSize; ++i)
    {
        curPos = (pos+i)%hashTable->maxSize;
        //如果当前位置为空，则插入该位置
        if(hashTable->data[curPos].type==EMPTY)
        {
            hashTable->data[curPos].key = key;
            //设置占据标记
            hashTable->data[curPos].type=LEGITIMATE;
            return curPos;
        }
        //如果当前位置不为空，而且值正好为Key，则返回
        if(hashTable->data[curPos].type==LEGITIMATE && hashTable->data[curPos].key==key)
            return curPos;
    }
    //Hash表已满
    return ERROR;
}

//释放Hash表内存
void FreeHashTable(HashTable *hashTable)
{
    //释放单元格数组内存
    free(hashTable->data);
    //释放整个hash表内存
    free(hashTable);
}

int main()
{
    int N, P, i, pos[MAX_N], key;
    HashTable *hashTable;

    //读入数据量N和Hash表长度P
    scanf("%d%d", &N, &P);
    //创建Hash表
    hashTable = CreateHashTable(P);
    //读入N个关键字
    for(i=0;i<N; ++i)
    {
        scanf("%d", &key);
        //将key插入到Hash表
        pos[i] = Insert(hashTable, key);
    }
    //释放Hash表
    free(hashTable);
    //打印结果
    for(i=0; i<N; ++i)
    {
        if(i)
            printf(" ");
        printf("%d", pos[i]);
    }
    printf("\n");
	return 0;
}
