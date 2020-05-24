bool Delete( HashTable H, ElementType Key )
{
    Index pos = Hash( Key, H->TableSize );
    struct LNode *pre, *node;
    pre = &(H->Heads[pos]);
    node = pre->Next;
    while(node)
    {
        if(strcmp(node->Data, Key)==0)
        {
            pre->Next = node->Next;
            free(node);
            printf("%s is deleted from list Heads[%d]\n", Key, pos);
            return true;
        }
        pre = node;
        node = node->Next;
    }
    return false;
}