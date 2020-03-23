//通过二分查找法找到合适的插入位置
bool Insert( List L, ElementType X )
{
	//lastValidPos表示一个合适的插入位置
    int begin=0, end= L->Last, mid, i, lastValidPos=-1;
	//线性表已满
    if(L->Last==MAXSIZE-1)
      return false;
    while(begin<=end)
    {
        mid = begin+(end-begin)/2;
		//该元素已经在排序好的数组中存在，则返回false
        if(X==L->Data[mid])
        {
            return false;
        }
        else if(X<L->Data[mid])
        {
            begin = mid+1;
        }
        else
        {
            end = mid-1;
            lastValidPos = mid;
        }
    }
	//如果还没有合适的插入位置，则表示要添加到尾部
    if(lastValidPos==-1)
        lastValidPos = L->Last+1;
	//从后往前移动数组内容
    for(i=L->Last; i>=lastValidPos; --i)
    {
        L->Data[i+1] = L->Data[i];
    }
	//插入新值
    L->Data[lastValidPos]=X;
	//数组最大下标加1
    ++L->Last;
    return true;
}
