#include <stdio.h>
#include <stdlib.h>

//二叉树里最多元素个数
#define MAX_N 1001
//从当前结点向上到根结点的最大路径长度log(MAX_N)
#define MAX_PATH_LEN 11

int main()
{
    int i, j, n, ancestorID=1;
    //i结点到根节点路径，j结点到根节点的路径，i和j路径长度
    int pathI[MAX_PATH_LEN], pathJ[MAX_PATH_LEN], iLen=0, jLen=0;
    //树结点从下标1开始存储
    int treeNodes[MAX_N];

    scanf("%d", &n);
    //读入n个二叉树结点值
    for(i=1; i<=n; ++i)
        scanf("%d", treeNodes+i);
    //读入i和j
    scanf("%d%d", &i, &j);
    //如果i结点为空
    if(treeNodes[i]==0)
        printf("ERROR: T[%d] is NULL\n", i);
    //如果j结点为空
    else if(treeNodes[j]==0)
        printf("ERROR: T[%d] is NULL\n", j);
    else
    {
        //从i向根节点追踪路径
        while(i!=0)
        {
            pathI[iLen++] = i;
            i/=2;
        }
        //从j向根节点追踪路径
        while(j!=0)
        {
            pathJ[jLen++] = j;
            j/=2;
        }
        //从根路径向下找最近公共祖先的编号
        for(i=iLen-1, j=jLen-1; pathI[i]==pathJ[j]; --i, --j)
            ancestorID = pathI[i];
        //打印祖先编号和值
        printf("%d %d\n", ancestorID, treeNodes[ancestorID]);
    }
    return 0;
}
