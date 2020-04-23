void PreorderPrintLeaves( BinTree BT )
{
    if(!BT)
      return;
    if(!BT->Left && !BT->Right)
        printf(" %c", BT->Data);
    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
}