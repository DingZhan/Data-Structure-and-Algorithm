#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001

//二叉搜索树(BST)结点
typedef struct TreeNode_
{
    int v;
    struct TreeNode_ *left;
    struct TreeNode_ *right;
}TreeNode;

//BST结点插入函数
TreeNode* InsertBST(TreeNode* root, int v)
{
    if(!root)
    {
        root = (TreeNode*)malloc(sizeof(TreeNode));
        root->v = v;
        root->left = root->right = NULL;
        return root;
    }
    if(v<root->v)
        root->left = InsertBST(root->left, v);
    //允许相同的值插入到右子树，这点要小心处理
    else //if(v>=root->v)
        root->right = InsertBST(root->right, v);
    return root;
}

//利用一个数组构建BST树（前序遍历的数组）
TreeNode* BuildBST(int preorder[], int n)
{
    TreeNode *root = NULL;
    int i;
    for(i=0; i<n; ++i)
        root = InsertBST(root, preorder[i]);
    return root;
}

//镜像生成另一棵BST
TreeNode* Mirror(TreeNode* root)
{
    if(!root)
        return NULL;
    TreeNode *root2 = (TreeNode*)malloc(sizeof(TreeNode));
    root2->v = root->v;
    //左右镜像当前结点
    root2->left = Mirror(root->right);
    root2->right = Mirror(root->left);
    return root2;
}

//把BST前序遍历的结果存在pre数组中
void PreOrderTraversal(TreeNode* root, int pre[], int *cur)
{
    if(!root)
        return;
    pre[(*cur)++] = root->v;
    PreOrderTraversal(root->left, pre, cur);
    PreOrderTraversal(root->right, pre, cur);
}

//打印后续遍历结果，bFirst表示是否需要打印前置空格
void PostOrderTraversal(TreeNode* root, int *bFirst)
{
    if(!root)
        return;
    PostOrderTraversal(root->left, bFirst);
    PostOrderTraversal(root->right, bFirst);
    if((*bFirst)==0)
        printf(" ");
    printf("%d", root->v);
    (*bFirst) = 0;
}

//后序遍历释放BST
void FreeTree(TreeNode* root)
{
    if(!root)
        return;
    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main()
{
    int i, preorder[MAX_N], n, pre1[MAX_N], pre2[MAX_N];
    TreeNode *tree, *mirrorTree;
    int bPreorderSucc=1, bMirrorPreorderSucc=1;
    int bFirst=1;

    //读入前序遍历数组
    scanf("%d", &n);
    for(i=0; i<n; ++i)
        scanf("%d", preorder+i);

    //构建BST树
    tree = BuildBST(preorder, n);

    //镜像该树
    mirrorTree = Mirror(tree);

    //前序遍历存储到pre1数组中
    i=0;
    PreOrderTraversal(tree, pre1, &i);
    //前序遍历镜像树存储到pre2数组中
    i=0;
    PreOrderTraversal(mirrorTree, pre2, &i);

    //判断前序遍历是否和输入的前序遍历一致
    for(i=0; i<n; ++i)
    {
        if(pre1[i]!=preorder[i])
            bPreorderSucc = 0;
        if(pre2[i]!=preorder[i])
            bMirrorPreorderSucc = 0;
    }
    if(bPreorderSucc==0 && bMirrorPreorderSucc==0)
        printf("NO\n");
    else
    {
        printf("YES\n");
        //打印后续遍历结果
        if(bPreorderSucc)
            PostOrderTraversal(tree, &bFirst);
        else
            PostOrderTraversal(mirrorTree, &bFirst);
        printf("\n");
    }

    //释放树
    FreeTree(tree);
    FreeTree(mirrorTree);
    return 0;
}

