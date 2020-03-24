List Insert( List L, ElementType X )
{
    PtrToNode preNode = L, newNode;
    newNode = (PtrToNode)malloc(sizeof(struct Node));
    newNode->Data = X;
    //因为链表有额外的头结点，所以不用担心preNode为空
    while(preNode->Next && preNode->Next->Data<X)
    {
        preNode = preNode->Next;
    }
    //新结点插在preNode后面
    newNode->Next = preNode->Next;
    preNode->Next = newNode;
    return L;
}