#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 31

//二叉搜索树的结点结构体
typedef struct TreeNode_
{
    //树的名字
    char name[31];
    //树出现的次数
    int count;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

//向二叉树插入结点
TreeNode* Insert(TreeNode *root, const char* name)
{
    if(!root)
    {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        strcpy(node->name, name);
        node->count = 1;
        node->left = node->right = NULL;
        return node;
    }
    //不区分大小写
//    int r = stricmp(name, root->name);
    int r = strcasecmp(name, root->name);
    if(r<0)
        root->left = Insert(root->left, name);
    else if(r>0)
        root->right = Insert(root->right, name);
    else
        ++root->count;
    return root;
}

//二叉搜索树的中序遍历就是字典序的结果
void InorderTraversal(TreeNode* root, int n)
{
    if(!root)
        return;
    InorderTraversal(root->left, n);
    printf("%s %.4lf%%\n", root->name, root->count*100.0/n);
    InorderTraversal(root->right, n);
}

//后续遍历删除树
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
    TreeNode *root = NULL;
    char name[MAX_LEN];
    int i, N;

    scanf("%d", &N);
    //吃掉数字后面的一个回车
    gets(name);

    for(i=0; i<N; ++i)
    {
        //因为有空格，所以不能用scanf
        gets(name);
        root = Insert(root, name);
    }
    InorderTraversal(root, N);

    //清空树内存
    FreeTree(root);
    return 0;
}
