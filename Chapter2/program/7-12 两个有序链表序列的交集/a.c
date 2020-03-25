#include <stdio.h>
#include <stdlib.h>

typedef struct Node_
{
    int v;
    struct Node_ *next;
}Node;

Node* ReadLinkList()
{
    Node *head=NULL, *lastNode=NULL, *node;
    int v;
    while(scanf("%d", &v))
    {
        if(v==-1)
            break;
        node = (Node*)malloc(sizeof(Node));
        node->v = v;
        node->next = NULL;
        if(lastNode==NULL)
        {
            head = lastNode = node;
        }
        else
        {
            lastNode->next = node;
            lastNode = node;
        }
    }
    return head;
}

Node* Intersection(Node *S1, Node *S2)
{
    Node *node1, *node2, *node, *S3=NULL, *lastNode=NULL;
    node1 = S1;
    node2 = S2;
    while(node1 && node2)
    {
        if(node1->v==node2->v)
        {
            node = (Node*)malloc(sizeof(Node));
            node->v = node1->v;
            node->next = NULL;
            if(lastNode==NULL)
            {
                S3 = lastNode = node;
            }
            else
            {
                lastNode->next = node;
                lastNode = node;
            }

            node1 = node1->next;
            node2 = node2->next;
        }
        else if(node1->v<node2->v)
        {
            node1 = node1->next;
        }
        else
        {
            node2 = node2->next;
        }
    }
    return S3;
}

void FreeLinkList(Node **head)
{
    Node *node = *head, *next;
    while(node)
    {
        next = node->next;
        free(node);
        node = next;
    }
    *head = NULL;
}

void PrintLinkList(const Node* head)
{
    if(head==NULL)
    {
        printf("NULL\n");
        return;
    }
    const Node *node = head;
    while(node)
    {
        if(node!=head)
            printf(" ");
        printf("%d", node->v);
        node = node->next;
    }
}

int main()
{
    Node *S1, *S2, *S3;
    S1 = ReadLinkList();
    S2 = ReadLinkList();

    S3 = Intersection(S1, S2);
    PrintLinkList(S3);

    FreeLinkList(&S1);
    FreeLinkList(&S2);
    FreeLinkList(&S3);
    return 0;
}
