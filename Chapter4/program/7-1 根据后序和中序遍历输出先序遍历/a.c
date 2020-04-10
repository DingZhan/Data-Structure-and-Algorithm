#include <stdio.h>
#include <stdlib.h>

#define MAX_N 31

//定义二叉树结点结构体
typedef struct TreeNode_
{
    int v;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

//初始化二叉树，也就是把根结点初始化为空，要修改指针，必须传入指针的指针
void InitTree(TreeNode **root)
{
    *root = NULL;
}

//后序遍历删除树，释放所有动态分配的内存
void FreeTree(TreeNode *root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

//前序遍历二叉树
void PreOrderTraversal(TreeNode *root)
{
    if(!root)
        return;
    //留个前置空格
    printf(" %d", root->v);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

//递归地从后续遍历和中序遍历结果构建出一颗二叉树，这里传入一个二级指针，是因为函数需要修改树的根结点（动态分配内存）
void BuildTree(int post[], int in[], int n, TreeNode **root)
{
    int i, pos=-1, v;
    //如果遍历结果已经为空，则返回
    if(n==0)
        return;
    //后序遍历的最后一个值为树的根节点值
    v = post[n-1];

    //动态分配一个结点作为当前子树的根结点，设置结点值，设置左右子树为空
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->v = v;
    (*root)->left = (*root)->right = NULL;

    //在中序遍历中搜索根节点值的位置pos，从而区分左右子树
    for(i=0; i<n; ++i)
    {
        if(in[i]==v)
        {
            pos = i;
            break;
        }
    }
    //对照样例设置左子树遍历数组和数组大小，并且传入左子树指针的指针
    BuildTree(post, in, pos, &((*root)->left));
    //对照样例设置右子树遍历数组和数组大小，并且传入右子树指针的指针
    BuildTree(post+pos, in+pos+1, n-pos-1, &((*root)->right));
}

//递归地从后续遍历和中序遍历结果构建出一颗二叉树，通过返回值的方式返回树根
TreeNode* BuildTree2(int post[], int in[], int n)
{
    int i, pos=-1, v;
    //如果遍历结果已经为空，则返回
    if(n==0)
        return NULL;
    //后序遍历的最后一个值为树的根节点值
    v = post[n-1];

    TreeNode *root;
    //动态分配一个结点作为当前子树的根结点，设置结点值，设置左右子树为空
    root = (TreeNode*)malloc(sizeof(TreeNode));
    root->v = v;
    root->left = root->right = NULL;

    //在中序遍历中搜索根节点值的位置pos，从而区分左右子树
    for(i=0; i<n; ++i)
    {
        if(in[i]==v)
        {
            pos = i;
            break;
        }
    }
    //对照样例设置左子树遍历数组和数组大小
    root->left = BuildTree2(post, in, pos);
    //对照样例设置右子树遍历数组和数组大小
    root->right = BuildTree2(post+pos, in+pos+1, n-pos-1);
    return root;
}


int main()
{
    int post[MAX_N], in[MAX_N], i, n;
    TreeNode *root;
    //读入n结点数
    scanf("%d", &n);
    //读入后序遍历结果
    for(i=0; i<n; ++i)
        scanf("%d", post+i);
    //读入中序遍历结果
    for(i=0; i<n; ++i)
        scanf("%d", in+i);
    //初始化二叉树（根节点初始化为NULL）
    InitTree(&root);
    //从后续和中序遍历结果构建一颗二叉树
//    BuildTree(post, in, n, &root);
    root = BuildTree2(post, in, n);

    //打印前缀
    printf("Preorder:");
    //前序遍历二叉树
    PreOrderTraversal(root);
    //打印一个换行
    printf("\n");
    //释放树结点动态内存
    FreeTree(root);
    //安全操作，将根节点设置为空
    root = NULL;

    return 0;
}
