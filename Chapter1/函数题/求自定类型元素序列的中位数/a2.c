
//递归实现第K(kth)大元素的查找，left是待查找区间的左边界，right是待查找区间的右边界，temp是临时数组
ElementType FindKthLargest(ElementType A[], int kth, int left, int right, ElementType temp[])
{
	//S1RightPos表示S1集合的右边界，S2LeftPos表示S2集合的左边界
	//递归函数将A[left, right],分割成两个集合S1和S2，其中S1集合中所有元素值大于等于一个参考值e，S2集合中所有元素值小于这个参考值e
	//当S2集合为空时候，我们需要重新选择一个参考值（否则死循环），默认使用e=A[left],但如果该参考值导致S2集合为空，则我们需要选择下一个值，即A[left+1]，
	//考虑到整个集合元素值都相同的情况，我们需要一个offset变量控制下一个参考位置的选择，当left+offset>right时候，我们就可以断言A[left,right]所有数组元素都相同
    int S1RightPos, S2LeftPos, i, offset=0;
    ElementType e;
	//如果集合只有一个元素，直接返回
    if(left==right)
        return A[left];

DO_IT_AGAIN:
	//选择一个参考值
    e = A[left+offset];
	//初始集合S1和S2都为空
    S1RightPos=left;
    S2LeftPos=right;
	//根据参考值e，对A中元素归类到S1和S2，其中S1集合元素值大于等于e，S2元素值小于e
    for(i=left; i<=right; ++i)
    {
        if(A[i]>=e)
            temp[S1RightPos++] = A[i];
        else
            temp[S2LeftPos--] = A[i];
    }
	//S2集合为空，需要重新选择参考值
    if(S2LeftPos==right)
    {
        ++offset;
        //A[left,right]所有值都相同
        if(left+offset>right)
            return A[left];
        goto DO_IT_AGAIN;
    }
	//将temp[left,right]拷贝回A
    for(i=left; i<=right; ++i)
        A[i] = temp[i];
	//如果S1集合元素个数正好为kth，则返回参考值e
    if(S1RightPos-left==kth)
    {
        return e;
    }
	//如果kth在S1集合， 则递归在S1集合中查找kth大元素，唯一改变的是右边界变成S1RightPos-1
    else if(S1RightPos-left>kth)
    {
        return FindKthLargest(A, kth, left, S1RightPos-1, temp);
    }
	//如果kth在S2集合， 则递归在S2集合中查找kth-Size(S1)大元素，唯一改变的是左边界变成S1RightPos
    else
    {
        return FindKthLargest(A, kth-(S1RightPos-left), S1RightPos, right, temp);
    }
}

ElementType Median( ElementType A[], int N )
{
	//分配一个临时数组，这样递归函数内部不需要每次都分配临时数组，减少递归入栈出栈指令
	//result是中位数结果
    ElementType temp[MAXN], result;
	//调用递归函数查找第K大元素，这里K = (N+1)/2
    result  = FindKthLargest(A, (N+1)/2, 0, N-1, temp);
	//返回第K大元素的值
    return result;
}