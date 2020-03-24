#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

typedef struct Node_
{
    int v;
    struct Node_ *next;
}Node;

Node *ReadLinkList()
{
    int v;
    Node *head=NULL, *lastNode= NULL, *node;
    while(1)
    {
        scanf("%d", &v);
        if(v==-1)
            break;
        node = (Node*)malloc(sizeof(Node));
        node->v = v;
        node->next = NULL;
        if(lastNode==NULL)
        {
            head = node;
            lastNode = node;
        }
        else
        {
            lastNode->next = node;
            lastNode = node;
        }
    }
    return head;
}

void PrintLinkList(const Node *head)
{
    if(!head)
    {
        printf("NULL\n");
        return;
    }
    int bFirst=1;
    const Node *node = head;
    while(node)
    {
        if(!bFirst)
            printf(" ");
        printf("%d", node->v);
        node = node->next;
        bFirst = 0;
    }
    printf("\n");
}
void FreeLinkList(Node *head)
{
    Node *next;
    while(head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}
Node* MergeLinkList(Node* S1, Node*S2)
{
    Node *node1, *node2, *S3=NULL, *lastS3Node=NULL, *node;
    node1 = S1;
    node2 = S2;
    while(node1 && node2)
    {
        node = (Node*)malloc(sizeof(Node));
        node->next = NULL;
        if(node1->v<node2->v)
        {
            node->v = node1->v;
            node1 = node1->next;
        }
        else
        {
            node->v = node2->v;
            node2 = node2->next;
        }
        if(lastS3Node==NULL)
        {
            S3 = node;
            lastS3Node = node;
        }
        else
        {
            lastS3Node->next = node;
            lastS3Node = node;
        }
    }
    while(node1)
    {
        node = (Node*)malloc(sizeof(Node));
        node->next = NULL;
        node->v = node1->v;
        node1 = node1->next;
        if(lastS3Node==NULL)
        {
            S3 = node;
            lastS3Node = node;
        }
        else
        {
            lastS3Node->next = node;
            lastS3Node = node;
        }
    }
    while(node2)
    {
        node = (Node*)malloc(sizeof(Node));
        node->next = NULL;
        node->v = node2->v;
        node2 = node2->next;
        if(lastS3Node==NULL)
        {
            S3 = node;
            lastS3Node = node;
        }
        else
        {
            lastS3Node->next = node;
            lastS3Node = node;
        }
    }
    return S3;
}

int main()
{
    Node *S1, *S2, *S3;

    S1 = ReadLinkList();
    S2 = ReadLinkList();

    S3 = MergeLinkList(S1, S2);
    PrintLinkList(S3);

    FreeLinkList(S1);
    FreeLinkList(S2);
    FreeLinkList(S3);

    return 0;
}
