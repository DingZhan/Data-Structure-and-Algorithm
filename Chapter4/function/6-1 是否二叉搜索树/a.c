
int last = -1000000;
bool IsBST ( BinTree T )
{
    if(!T)
        return true;
    bool bLeft, bRight;

    bLeft = IsBST(T->Left);

    if(T->Data<=last)
        return false;
    last = T->Data;

    bRight = IsBST(T->Right);
    return bLeft && bRight;
}