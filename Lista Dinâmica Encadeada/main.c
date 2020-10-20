#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dataNode
{
    int index;
    int value;
} DataNode;

typedef struct node
{
    DataNode data;
    struct node *next;
} Node;

typedef struct list
{
    int size;
    Node *head;
} List;

void push(List *list, DataNode data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

int indexOf(List *list, Node *node)
{
    if (node == NULL)
    {
        printf("Node invalid !!\n");
        system("pause");
        return -1;
    }

    Node *pointer = list->head;

    int index = 0;

    while (pointer != node && pointer != NULL)
    {
        pointer = pointer->next;
        index++;
    }

    if (pointer != NULL)
    {
        return index;
    }
    else
    {
        printf("Node invalid !!\n");
        system("pause");
        return -1;
    }
}

Node *atPos(List *list, int index)
{
    if (index < 0 || index > list->size)
    {
        printf("Index invalid  !!\n");
        system("pause");
        return NULL;
    }

    Node *node = list->head;

    int i;
    for (i = 0; i < index; i++)
    {
        node = node->next;
    }
    return node;
}

Node *minValue(List *list, int index)
{
    Node *pointer = atPos(list, index);
    Node *minNode = pointer;

    while (pointer != NULL)
    {
        if (pointer->data.value < minNode->data.value)
        {
            minNode = pointer;
            minNode->data.index = index;
        }

        pointer = pointer->next;
        index++;
    }
    return minNode;
}

Node *maxValue(List *list, int index)
{
    Node *pointer = atPos(list, index);
    Node *maxNode = pointer;
 
    while (pointer != NULL)
    {
        if (pointer->data.value > maxNode->data.value)
        {
            maxNode = pointer;
            maxNode->data.index = index;
        }

        pointer = pointer->next;
        index++;
    }
    return maxNode;
}

bool listEmpty(List *list)
{
    return (list->size == 0);
}

void pop(List *list)
{
    if (listEmpty(list))
    {
        printf("The list is empty  !!\n");
        system("pause");
        return;
    }

    Node *pointer = list->head;

    list->head = pointer->next;
    free(pointer);
    list->size--;

    printf("The first number has been removed\n");
    system("pause");
}

void showList(List *list)
{
    if (listEmpty(list))
    {
        printf("The list is empty  !!\n");
        system("pause");
        return;
    }

    Node *pointer = list->head;
    int index = 0;
    while (pointer != NULL)
    {
        printf("Index: %d Value: %d \n", index, pointer->data.value);
        pointer = pointer->next;
        index++;
    }
    printf("\n");
    system("pause");
}

void changeNodes(List *list, Node *nodeA, Node *nodeB)
{
    if (nodeA == nodeB)
    {
        return;
    }

    int indexA = indexOf(list, nodeA);
    int indexB = indexOf(list, nodeB);

    if (indexA > indexB)
    {
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        indexA = indexB;
        indexB = indexOf(list, nodeA);
    }

    Node *pb = atPos(list, indexB - 1);

    if (nodeA == list->head)
    {
        list->head = nodeB;
    }
    else
    {
        Node *pa = atPos(list, indexA - 1);
        pa->next = nodeB;
    }

    pb->next = nodeA;

    Node *pointer = nodeA->next;
    nodeA->next = nodeB->next;
    nodeB->next = pointer;
}

void changeOrderDecreasing(List *list)
{
    int i;
    for (i = 0; i < list->size - 1; i++)
    {     
        changeNodes(list, atPos(list, i), maxValue(list, i));
    }
}

void changeOrderGrow(List *list)
{
    int i;
    for (i = 0; i < list->size -1; i++)
    {
        changeNodes(list, atPos(list, i), minValue(list,i));
    }
}

void erase(List *list, int index)
{
    if (index == 0)
    {
        pop(list);
    }
    else
    {
        Node *current = atPos(list, index);

        if (current == NULL)
        {
            printf("Index invalid  !!\n");
            system("pause");
            return;
        }

        Node *previous = atPos(list, index - 1);
        previous->next = current->next;
        free(current);
        list->size--;

        printf("Node removed  !!\n");
        system("pause");
    }
}

void insertValue(List *list, DataNode data, int index)
{

    if (index == 0)
    {
        push(list, data);
    }
    else
    {
        Node *current = atPos(list, index);

        if (current == NULL)
        {
            return;
        }

        Node *previous = atPos(list, index - 1);
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->data = data;
        previous->next = newNode;
        newNode->next = current;
        list->size++;
    }
}

List *createList()
{
    List *list = (List *)malloc(sizeof(List));

    list->size = 0;
    list->head = NULL;

    return list;
}

int menu(List *list)
{
    int option;

    system("cls");
    printf("    [Linked List]\n");
    printf("[-----[ MENU ]-----]\n");
    printf("[1] Insert new value in the list\n[2] Remove value\n[3] Change values\n[4] Show list\n[5] Show the lowest value in the list\n[6] Show the highest value in the list\n[7] Change Order\n[8] Exit\nOption: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
    {
        int option2;
        do
        {
            system("cls");
            printf("[-----[ INSERT VALUE OPTION ]-----]\n");
            printf("[1] Insert value in list\n[2] Insert value in a position in the list\nOption: ");
            scanf("%d", &option2);
        } while (option2 <= 0 || option2 > 2);

        DataNode data;
        int index = 0;

        if (option2 == 2)
        {
            printf("Enter index from insert node: ");
            scanf("%d", &index);
        }

        printf("Enter value from insert node: ");
        scanf("%d", &data.value);

        insertValue(list, data, index);
        break;
    }
    case 2:
    {
        int index;
        printf("Enter index from remove node: ");
        scanf("%d", &index);

        erase(list, index);

        break;
    }
    case 3:
    {
        int indexA, indexB;

        printf("Enter index the first node: ");
        scanf("%d", &indexA);

        printf("Enter index the second node: ");
        scanf("%d", &indexB);

        if (atPos(list, indexA) != NULL && atPos(list, indexB) != NULL)
        {
            changeNodes(list, atPos(list, indexA), atPos(list, indexB));

            printf("Nodes changed !!\n");
            system("pause");
        }

        break;
    }
    case 4:
    {
        showList(list);
        break;
    }
    case 5:
    {
        if (!listEmpty(list))
        {
            printf("Index: %d Value: %d\n", minValue(list, 0)->data.index, minValue(list, 0)->data.value);
        }
        else
        {
            printf("The list is empty  !!\n");
        }
        system("pause");
        break;
    }
    case 6:
    {
        if (!listEmpty(list))
        {
            printf("Index: %d Value: %d\n", maxValue(list, 0)->data.index, maxValue(list, 0)->data.value);
        }
        else
        {
            printf("The list is empty  !!\n");
        }
        system("pause");
        break;
    }
    case 7:
    {
        if (!listEmpty(list) && list->size > 1)
        {
            int option2;
            do
            {
                system("cls");
                printf("[-----[ CHANGE TYPE OPTION ]-----]\n");
                printf("[1] Growing\n[2] Decreasing\nOption: ");
                scanf("%d", &option2);
            } while (option2 <= 0 || option2 > 2);

            switch (option2)
            {
            case 1:
            {
                changeOrderGrow(list);
                printf("Growing  !!\n");
                break;
            }
            case 2:
            {
                changeOrderDecreasing(list);
                printf("Decreasing  !!\n");
                break;
            }
            }
        }
        else
        {
            printf("The list is empty  !!\n");
        }
        system("pause");
        break;
    }
    case 8:
    {
        break;
    }
    default:
    {
        printf("Invalid option !\n");
        system("pause\n");
    }
    }
    return option;
}

int main()
{
    List *list = createList();
    int option;

    do
    {
        option = menu(list);
    } while (option != 8);

    printf("The program is ending...\n");

    return 0;
}