#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 11

//二叉树结点结构体
typedef struct TreeNode_
{
    //结点编号
    int id;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

//树中间结构体类型，为了建树
typedef struct TreeData_
{
    //左儿子编号
    int left;
    //右儿子编号
    int right;
}TreeData;

//根据中间结构体数组建立二叉树
TreeNode* BuildTree(TreeData *data, int n)
{
    int i;
    int tags[MAX_N]={0};
    TreeNode *nodes[MAX_N];
    TreeNode *root = NULL;
    //设置tags标记位，用来表示该结点有父节点，所以最终没有父节点的结点就是根结点
    for(i=0; i<n; ++i)
    {
        if(data[i].left!=-1)
            tags[data[i].left] = 1;
        if(data[i].right!=-1)
            tags[data[i].right] = 1;
        nodes[i] = (TreeNode*)malloc(sizeof(TreeNode));
        nodes[i]->id = i;
        nodes[i]->left = nodes[i]->right = NULL;
    }
    //找根结点root，没有父节点的结点就是根结点
    for(i=0; i<n; ++i)
    {
        if(tags[i]==0)
        {
            //多个根结点存在
            if(root)
            {
                root = NULL;
                break;
            }
            root = nodes[i];
        }
        //设置结点的左右儿子
        if(data[i].left!=-1)
            nodes[i]->left = nodes[data[i].left];
        if(data[i].right!=-1)
            nodes[i]->right = nodes[data[i].right];
    }
    //没有根结点，或者有多个根结点错误
    if(!root)
    {
        for(i=0; i<n; ++i)
            free(nodes[i]);
        return NULL;
    }
    return root;
}

//后续遍历删除树内存
void FreeTree(TreeNode *root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

//队列，用来层序遍历
typedef struct Queue_
{
    TreeNode* data[MAX_N];
    int front;
    int rear;
}Queue;

Queue* CreateQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = 0;
    return q;
}

int IsEmpty(Queue*q)
{
    return q->front==q->rear;
}
int IsFull(Queue* q)
{
    return (q->rear+1)%MAX_N == q->front;
}
int Enque(Queue*q, TreeNode* node)
{
    if(IsFull(q))
        return 0;
    q->rear = (q->rear+1)%MAX_N;
    q->data[q->rear] = node;
    return 1;
}
TreeNode* Deque(Queue*q)
{
    if(IsEmpty(q))
        return NULL;
    q->front = (q->front+1)%MAX_N;
    return q->data[q->front];
}
void FreeQueue(Queue*q)
{
    free(q);
}

void LevelOrderTraversal(TreeNode *root)
{
    if(!root)
        return;
    int tag=0;
    //创建队列
    Queue* q = CreateQueue();
    //先把根入队
    Enque(q, root);
    TreeNode *node;
    while(!IsEmpty(q))
    {
        //出队
        node = Deque(q);
        //如果该结点为叶子结点，则打印
        if(!node->left && !node->right)
        {
            if(tag)
                printf(" ");
            printf("%d", node->id);
            tag = 1;
        }
        //左儿子入队
        if(node->left)
            Enque(q, node->left);
        //右儿子入队
        if(node->right)
            Enque(q, node->right);
    }
    printf("\n");
    //释放队列
    FreeQueue(q);
}

int main()
{
    //中间结构体数组，建树用的
    TreeData data[MAX_N];
    int i, n;
    //树根
    TreeNode *root;
    char lineStr[10], str1[10], str2[10];

    //用fgets得到一行字符串
    fgets(lineStr, 10, stdin);
    //得到n个结点信息
    n = atoi(lineStr);
    //读取n个结点
    for(i=0; i<n; ++i)
    {
        //继续使用fgets避免吃空格问题
        fgets(lineStr, 10, stdin);
        //从一行字符串中格式化出两个子串
        sscanf(lineStr, "%s%s", str1, str2);
        if(str1[0]=='-')
            data[i].left = -1;
        else
            data[i].left = atoi(str1);
        if(str2[0]=='-')
            data[i].right = -1;
        else
            data[i].right = atoi(str2);
    }
    //建立二叉树
    root = BuildTree(data, n);
    //层序遍历
    LevelOrderTraversal(root);
    //释放树内存
    FreeTree(root);
    return 0;
}
