//从当前树根结点找一条路径到子树目标结点，该子树目标结点值为value
//路径存储在path数组中，路径中结点个数为n
int FindPath(Tree T, int value, int path[], int *n)
{
    //当前结点已为空，所以该树中没有该目标结点，返回失败值
    if(!T)
        return 0;
    //把当前结点值存在访问路径中，访问路径结点数要加1
    path[(*n)++] = T->Key;
    //如果目标值小于当前结点值，则往左子树搜索
    if(value<T->Key)
        return FindPath(T->Left, value, path, n);
    //如果目标值大于当前结点值，则往右子树搜索
    else if(value>T->Key)
        return FindPath(T->Right, value, path, n);
    //找到该目标节点，返回成功值
    else
        return 1; //Find it
}
//定义路径中结点最大数目
#define MAX_N 1000
//定义一个无效的结点值
#define INVALID_V -10000000
//u和v结点的最近公共祖先
int LCA( Tree T,  int u, int v )
{
    //定义两条路径分别为u和v结点，路径节点数目存储在nu和nv中
    int pathU[MAX_N], pathV[MAX_N], nu=0, nv=0;
    //lastSame表示上一个最近公共祖先值，初始设置为无效值
    int i, lastSame=INVALID_V;
    //从根结点找目标节点u
    if(!FindPath(T, u, pathU, &nu))
        return ERROR;
    //从根节点找目标节点v
    if(!FindPath(T, v, pathV, &nv))
        return ERROR;
    //正向判断路径中相同的结点，碰到不同的结点就退出
    for(i=0; i<nu && i<nv; ++i)
    {
        if(pathU[i]!=pathV[i])
            break;
        lastSame = pathU[i];
    }
    //如果最近公共祖先依然是个无效值，则没有公共祖先
    if(lastSame==INVALID_V)
        return ERROR;
    else//返回最近公共祖先
        return lastSame;
}
