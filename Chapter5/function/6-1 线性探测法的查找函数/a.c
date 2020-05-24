Position Find( HashTable H, ElementType Key )
{
    Position pos  = Hash(Key,  H->TableSize );
    Position curPos;
    int i;
    //如果该位置元素为空，则直接返回
    if(H->Cells[pos].Info==Empty)
        return pos;
    //如果该位置已经有元素,并且该元素就是待查找的值,直接返回该位置
    if(H->Cells[pos].Info == Legitimate && H->Cells[pos].Data==Key)
        return pos;
    //线性探测之后位置
    for(i=1; i<H->TableSize; ++i)
    {
        curPos = (pos+i)%H->TableSize;
        //如果当前位置没被占据，则说明Key不在hash表里，返回该位置
        if(H->Cells[curPos].Info==Empty)
            return curPos;
        //如果当前位置被占据，并且值就是Key，则查找成功
        if(H->Cells[curPos].Info==Legitimate && H->Cells[curPos].Data==Key)
            return curPos;
    }
    return ERROR;
}