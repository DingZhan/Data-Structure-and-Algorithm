#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//hash表长度
#define MAX_N 100003
//每行最多的字符数141,但最后一个测试用例始终无法通过，所以猜测#可能不算在140个字符内
#define MAX_LEN 150
//一行最多的话题数目 141/3 < 50
#define MAX_TOPIC_ONE_LINE 50

//hash表链式表示的结点结构体
typedef struct Node_
{
    //话题关键字
    char topic[MAX_LEN];
    //该话题出现的总次数
    int count;
    //next指针
    struct Node_* next;
}Node;

//hash表结构体
typedef struct HashTable_
{
    //链表头数组
    Node *heads;
    //数组总长度，以及hash函数对应的质数
    int size; //a prime number
}HashTable;

//创建Hash表
HashTable* CreateHashTable(int size)
{
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    //分配链表表头数组，初始所有表头内容都为0 (calloc)
    hashTable->heads = (Node*)calloc(size, sizeof(Node));
    //设置hash表长度
    hashTable->size = size;
    return hashTable;
}

//hash函数：从关键字映射到hash表具体下标
int Hash(HashTable *hashTable, const char *topic)
{
    int code=0;
    //采用字符串移位法
    for(; (*topic)!='\0'; ++topic)
        code = code*10+(*topic);
    //防止越界为负数，所以先取模，再加hash表长度，最后再取模
    code = (code%hashTable->size+hashTable->size)%hashTable->size;
    return code;
}

//向hash表里插入一个关键字，返回该关键字已经出现的次数
int Insert(HashTable *hashTable, const char *topic)
{
    //找到待插入的位置
    int pos = Hash(hashTable, topic);
    //从该位置的链表头开始遍历搜索该关键字是否出现过
    Node* node = hashTable->heads[pos].next;
    while(node)
    {
        //该关键字出现过，则把计数器+1后返回
        if(strcmp(node->topic, topic)==0)
        {
            ++node->count;
            return node->count;
        }
        node = node->next;
    }
    //该关键字为新关键字，之前未出现过，因此把该关键字结点加入到链表头位置
    node = (Node*)malloc(sizeof(Node));
    strcpy(node->topic, topic);
    node->count = 1;
    node->next = hashTable->heads[pos].next;
    hashTable->heads[pos].next = node;
    //返回1，因为是新关键字
    return node->count;
}

//释放Hash表内存
void ReleaseHashTable(HashTable* hashTable)
{
    //释放链表头数组内存
    free(hashTable->heads);
    //释放hash表内存
    free(hashTable);
}

//下一个质数
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

//清洗该主题，替换一些符号字符，去掉多余的空格，
void CleanTopic(char *topic)
{
    int i, j, len;
    len  = strlen(topic);
    for(i=0, j=0; i<len; ++i)
    {
        //如果当前是字符或数字，则保留
        if(isalpha(topic[i]) || isdigit(topic[i]))
        {
            topic[j++] = topic[i];
        }
        //如果当前是空格或其他字符，则判断它之前是否已经是个空格，不能记录多余的空格
        else// if(topic[i]==' ')
        {
            if(j>0 && topic[j-1]!=' ')
                topic[j++] = ' ';
        }
    }
    //消除末尾的一个空格
    if(j>0 && topic[j-1]==' ')
        topic[j-1] = '\0';
    else
        topic[j] = '\0';
    //首字母大写
    if(isalpha(topic[0]))
    {
        topic[0] = toupper(topic[0]);
    }
}

int main()
{
    char str[MAX_LEN], topic[MAX_LEN], *p, *startP, *endP, hotTopic[MAX_LEN];
    char lineTopics[MAX_TOPIC_ONE_LINE][MAX_LEN];
    int i, j, N, ret, maxCount=0, maxCountNum=0, count, topicCountCurLine=0;

    //创建热门话题关键字的hash表
    HashTable *hashTable = CreateHashTable(MAX_N);
    //读入微博个数N
    scanf("%d", &N);
    //吃掉行末尾的空格
    fgets(str, MAX_LEN, stdin);
    //读入N条微博
    for(i=0; i<N; ++i)
    {
        //重置当前一行微博的话题个数为0
        topicCountCurLine = 0;
        //得到一行微博
        fgets(str, MAX_LEN, stdin);
        //去掉末尾的回车键
        str[strlen(str)-1] = '\0';
        //利用成对的#切分话题
        p = str;
        while(1)
        {
            //找到p后的第一个#
            startP = strchr(p, '#');
            if(startP==NULL)
                break;
            //找到p后的第二个#
            endP = strchr(startP+1, '#');
            if(endP==NULL)
                break; //按照上下文，#成对出现，应该不会发生不成对情况
            //把两个#之间的字符串提取出来
            for(j=1; startP[j]!='#'; ++j)
                topic[j-1] = tolower(startP[j]);
            //末尾加个\0
            topic[j-1] = '\0';
            CleanTopic(topic);
//          printf("new topic: %s\n", topic);

            p = endP+1;
            //如果当前行中该话题已经出现过，则不要再计数了
            for(j=0; j<topicCountCurLine; ++j)
            {
                if(!strcmp(topic, lineTopics[j]))
                    break;
            }
            //当前行中该话题已出现过，直接跳过
            if(j!=topicCountCurLine)
                continue;
            //把当前话题拷贝到当前行的话题列表中
            strcpy(lineTopics[topicCountCurLine++], topic);
            //把当前话题插入hash表
            count = Insert(hashTable, topic);
            //如果该话题出现的次数大于最大次数，则更新最大次数
            if(count>maxCount)
            {
                //更新最大次数
                maxCount = count;
                //重置最大次数同次数的话题数为1
                maxCountNum = 1;
                //重置最热话题
                strcpy(hotTopic, topic);
            }
            //如果该话题出现的次数等于最大次数，则要更具字典序更新最热话题
            else if(count==maxCount)
            {
                ret = strcmp(topic, hotTopic);
                //当前话题比最热话题的字典序靠前，则更新最热话题
                if(ret<0)
                    strcpy(hotTopic, topic);
                //同次数话题+1
                ++maxCountNum;
            }
        }
    }
    //打印最热话题
    printf("%s\n", hotTopic);
    //打印该话题出现的微博条数
    printf("%d\n", maxCount);
    //和该话题同样热度的其他话题个数
    if(maxCountNum>1)
        printf("And %d more ...\n", maxCountNum-1);

    //释放hash表内存
    ReleaseHashTable(hashTable);
    return 0;
}
