int GetHeight( BinTree BT )
{
    if(!BT)
      return 0;
    int left = GetHeight(BT->Left);
    int right = GetHeight(BT->Right);
    return (left>right?left:right)+1;
}