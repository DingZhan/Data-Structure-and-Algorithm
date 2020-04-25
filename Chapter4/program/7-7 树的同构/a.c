#include <stdio.h>
#include <stdlib.h>

#define MAX_N 11

//树结点结构体
typedef struct TreeNode_
{
    char d;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

//树中间数据结构体，该结构体为了创建树而设立的
typedef struct TreeData_
{
    char d;
    //左儿子在数组中的索引下标
    int leftIndex;
    //右儿子在数组中的索引下标
    int rightIndex;
}TreeData;

//根据中间数据构建二叉树
TreeNode* BuildTree(TreeData td[], int N)
{
    int i;
    //tags数组是为了搜索树根结点而设置的，根节点不是任何一个结点的儿子
    //所以它的tag标记应为0
    int tags[MAX_N] = {0};
    //为每个td元素创建一个树结点
    TreeNode *nodes[MAX_N]={0};
    //树根结点
    TreeNode *root=NULL;
    //遍历中间数组，设置tags标记位
    for(i=0; i<N; ++i)
    {
        //如果左儿子不为空，设置左儿子的tag标记位
        if(td[i].leftIndex!=-1)
            tags[td[i].leftIndex] = 1;
        //如果右儿子不为空，设置右儿子的tag标记位
        if(td[i].rightIndex!=-1)
            tags[td[i].rightIndex] = 1;
        //动态分配一个结点
        nodes[i] = (TreeNode*)malloc(sizeof(TreeNode));
        nodes[i]->d = td[i].d;
        //初始化左右儿子都为空
        nodes[i]->left = nodes[i]->right = NULL;
    }
    //搜索树根结点，同时装配好整棵树
    for(i=0; i<N; ++i)
    {
        //找到树根结点
        if(tags[i]==0)
        {
            //存在多个树根结点，因此创建失败
            if(root)
            {
                root = NULL;
                break;
            }
            root = nodes[i];
        }
        //设置左儿子结点指针
        if(td[i].leftIndex!=-1)
            nodes[i]->left = nodes[td[i].leftIndex];
        //设置右儿子结点指针
        if(td[i].rightIndex!=-1)
            nodes[i]->right = nodes[td[i].rightIndex];
    }

    //多个树根或者没有树根
    if(!root)
    {
        //失败的话也要记得释放内存
        for(i=0; i<N; ++i)
            free(nodes[i]);
        return NULL;
    }
    //成功建树，返回树根
    return root;
}

//判断两棵树是否同构
int IsHomogeny(TreeNode* t1,TreeNode* t2)
{
    //如果子树根结点一个为空，另一个不为空则一定不同构
    if(t1 && !t2 || !t1 && t2)
        return 0;
    //如果两个都为空，则同构
    if(!t1 && !t2)
        return 1;
    //如果值都不一样，则不同构
    if(t1->d!=t2->d)
        return 0;
    //如果左左同构并且右右同构，则整棵树同构
    if(IsHomogeny(t1->left, t2->left)&&IsHomogeny(t1->right, t2->right))
        return 1;
    //如果左右同构并且右左同构，则整棵树同构
    else if(IsHomogeny(t1->left, t2->right)&&IsHomogeny(t1->right, t2->left))
        return 1;
    //否则，不同构
    else
        return 0;
}

//记得用后续遍历释放树的内存
void FreeTree(TreeNode *root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main()
{
    TreeData td[MAX_N];
    int i, N;
    char idStr[2], idStr2[2];
    TreeNode *tree1, *tree2;

    //读取第一棵树
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        //吃掉回车
        gets(idStr);
        scanf("%c%s%s", &td[i].d, idStr, idStr2);
        if(idStr[0]=='-')
            td[i].leftIndex = -1;
        else
            td[i].leftIndex = atoi(idStr);
        if(idStr2[0]=='-')
            td[i].rightIndex = -1;
        else
            td[i].rightIndex = atoi(idStr2);
    }
    //建立第一棵树
    tree1 = BuildTree(td, N);

    //读取第二棵树
    scanf("%d", &N);
    for(i=0; i<N; ++i)
    {
        //吃掉回车
        gets(idStr);
        scanf("%c%s%s", &td[i].d, idStr, idStr2);
        if(idStr[0]=='-')
            td[i].leftIndex = -1;
        else
            td[i].leftIndex = atoi(idStr);
        if(idStr2[0]=='-')
            td[i].rightIndex = -1;
        else
            td[i].rightIndex = atoi(idStr2);
    }
    //构建第二棵树
    tree2 = BuildTree(td, N);

    //判断同构
    if(IsHomogeny(tree1, tree2))
        printf("Yes\n");
    else
        printf("No\n");

    //释放树内存
    FreeTree(tree1);
    FreeTree(tree2);
    return 0;
}

