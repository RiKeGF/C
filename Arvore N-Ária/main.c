#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int index = 0;

typedef struct dataNode
{
    int index;
    int value;
} DataNode;

typedef struct node
{
    DataNode data;
    struct node *next;
    struct node *back;
} Node;

void showTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("Index: %d Value: %d\n", root->data.index, root->data.value);
    Node *p = root->back;
    while (p)
    {     
         showTree(p);    
         p = p->next;    
    }
}

Node *createNewNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->back = NULL;
    node->next = NULL;
    node->data.index = index++;
    node->data.value = value;
    return node;
}

Node *getValue(int value, Node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data.value == value)
    {
        return root;
    }
    Node *p = root->back;
    while (p)
    {
        Node *r = getValue(value, p);
        if (r)
        {
            return r;
        }
        p = p->next;
    }
    return NULL;
}

bool insertValue(Node *root, int value, int valueP)
{
    Node *p = getValue(valueP, root);
    if (!p)
    {
        return false;
    }
    Node *newNode = createNewNode(value);
    Node *pointer = p->back;
    if (!pointer)
    {
        p->back = newNode;
    }
    else
    {
        while (p->next)
        {
            p = p->next;
        }
        p->next = newNode;
    }
    return true;
}

int main()
{
    Node *node = NULL;
    int option;

    do
    {
        system("cls");
        printf("    [Tree N-Aria]\n");
        printf("[-----[ MENU ]-----]\n");
        printf("[1] Create new node\n[2] Insert new value\n[3] Show tree\n[4] Exit\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            int value;

            printf("\nEnter first value: ");
            scanf("%d", &value);

            node = createNewNode(value);

            printf("Node created !!\n");
            system("pause");

            break;
        }
        case 2:
        {
            int value;
            int valueP;

            if (node != NULL)
            {
                printf("\nEnter value: ");
                scanf("%d", &value);

                printf("\nEnter the parent value: ");
                scanf("%d", &valueP);

                insertValue(node, value, valueP);
            }
            else
            {
                printf("A tree has not yet been created !!\n");
                system("pause");
            }

            break;
        }
        case 3:
        {
            if (node != NULL)
            {
                showTree(node);
            }
            else
            {
                printf("A tree has not yet been created !!\n");
            }

            system("pause");
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            printf("Option invalid !!\n");
            system("pause");
            break;
        }
        }

    } while (option != 4);

    printf("The program is ending...\n");

    return 1;
}