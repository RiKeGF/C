#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct No
{
    int value;
    struct No *back;
    struct No *next;
} Node;

void insertValue(Node **pRoot, int value)
{
    if (*pRoot == NULL)
    {
        *pRoot = (Node *)malloc(sizeof(Node));
        (*pRoot)->back = NULL;
        (*pRoot)->next = NULL;
        (*pRoot)->value = value;
    }
    else
    {
        if (value < (*pRoot)->value)
        {
            insertValue(&(*pRoot)->back, value);
        }
        else
        {
            insertValue(&(*pRoot)->next, value);
        }
    }
}

void removeValue(Node **pRoot, int value)
{
    if (*pRoot == NULL)
    {
        printf("Number not exists !!\n");
        system("pause");
        return;
    }
    if (value < (*pRoot)->value)
    {
        removeValue(&(*pRoot)->back, value);
    }
    else if (value > (*pRoot)->value)
    {
        removeValue(&(*pRoot)->next, value);
    }
    else
    {
        Node *pAux = *pRoot;
        if ((pAux->back == NULL) && (pAux->next == NULL))
        {
            free(pAux);
            (*pRoot) = NULL;
        }
        else
        {
            if (pAux->back == NULL)
            {
                (*pRoot) = (*pRoot)->next;
                pAux->next = NULL;
                free(pAux);
                pAux = NULL;
            }
            else
            {
                if (pAux->next == NULL)
                {
                    (*pRoot) = (*pRoot)->back;
                    pAux->back = NULL;
                    free(pAux);
                    pAux = NULL;
                }
                else
                {
                    pAux = pAux->next;
                    pAux->back = (*pRoot)->back;
                    pAux->next = (*pRoot)->next;
                    (*pRoot)->back = (*pRoot)->next = NULL;
                    free((*pRoot));
                    *pRoot = pAux;
                    pAux = NULL;
                }
            }
        }
    }
}

void showTree(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }
    showTree(pRoot->back);
    printf("%d\n", pRoot->value);
    showTree(pRoot->next);
}

int countNode(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + countNode(pRoot->back) + countNode(pRoot->next);
    }
}

int bigger(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int height(Node *pRoot)
{
    if (pRoot == NULL || (pRoot->back == NULL && pRoot->next == NULL))
    {
        return 0;
    }
    else
    {
        return 1 + bigger(height(pRoot->back), height(pRoot->next));
    }
}

int getValue(Node *pRoot, int value)
{
    Node *temp = pRoot;
    bool stop = false;

    if (temp == NULL)
    {
        return NULL;
    }
    else if (temp->back == NULL && temp->next == NULL)
    {
        if (temp->value == value)
        {
            return value;
        }
        else
        {
            return NULL;
        }
    }
    else if (temp->value == value)
    {
        return value;
    }
    else
    {
        while (!stop)
        {
            if (temp->value < value)
            {
                if (temp->back == NULL)
                {
                    stop = true;
                    if (temp->value == value)
                    {
                        return value;
                    }
                    else
                    {
                        return NULL;
                    }
                }
                else
                {
                    temp = temp->next;
                    if (temp->value == value)
                    {
                        return value;
                    }
                }
            }
            else if (temp->value > value)
            {
                if (temp->next == NULL)
                {
                    stop = true;
                    if (temp->value == value)
                    {
                        return value;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    temp = temp->back;
                    if (temp->value == value)
                    {
                        return value;
                    }
                }
            }
        }
    }
}

int main()
{
    Node *node = NULL;
    int option;

    do
    {
        system("cls");
        printf("    [Tree Binary]\n");
        printf("[-----[ MENU ]-----]\n");
        printf("[1] Insert new value\n[2] Remove value\n[3] Count Nodes\n[4] Height Tree\n[5] Show Tree\n[6] Exit\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            int value;

            printf("\nEnter value: ");
            scanf("%d", &value);

            insertValue(&node, value);

            printf("Value entered !!\n");

            system("pause");

            break;
        }
        case 2:
        {
            int value;

            printf("\nEnter value: ");
            scanf("%d", &value);

            removeValue(&node, value);

            printf("Value removed !!\n");

            system("pause");

            break;
        }
        case 3:
        {
            if (node != NULL)
            {
                int count = countNode(node);

                printf("The tree has %d nodes !!\n", count);
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
            if (node != NULL)
            {
                int count = height(node);

                printf("The tree is %d tall !!\n", count);
            }
            else
            {
                printf("A tree has not yet been created !!\n");
            }

            system("pause");

            break;
        }
        case 5:
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
        case 6:
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

    } while (option != 6);

    printf("The program is ending...\n");

    return 1;
}