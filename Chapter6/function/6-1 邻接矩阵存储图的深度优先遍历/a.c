//深度优先遍历
void DFS( MGraph Graph, Vertex V, void (*Visit)(Vertex) )
{
    int i;
    //设置当前顶点V已经被访问
    Visited[V] = true;
    //访问顶点V
    Visit(V);
    //遍历顶点V的所有未被访问过的邻接顶点
    for(i=0; i<Graph->Nv; ++i)
    {
        if(i==V)
            continue;
        //如果顶点i和V之间有边，并且顶点i未被访问过，则递归调用DFS
        if(Graph->G[V][i]!=INFINITY && Visited[i]==false)
        {
           DFS(Graph, i, Visit);
        }
     }
}