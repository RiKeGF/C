#include <stdio.h>
#include <stdbool.h>
#define MAX 10

int start = 0;
int end = 0;
int stack[MAX];

void push(int value)
{
    stack[end++] = value;
}

void pop()
{
    stack[--end] = 0;
}

bool stackEmpty()
{
    return start == end;
}

bool stackFull()
{
    return end == MAX;
}

int main()
{
    int value;
    int option;
    bool showStack = true;

    do
    {
        system("cls");
        printf("[-----[ Stack ]-----]\n");
        if (stackFull())
        {
            printf("State: Full\n");
        }
        else if (stackEmpty())
        {
            printf("State: Empty\n");
        }
        else
        {
            printf("State: Released\n");
        }
        if (showStack)
        {
            for (size_t i = 0; i < MAX; i++)
            {
                printf("[%d] %d\t", i, stack[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < end; i++)
            {
                printf("[%d] %d\t", i, stack[i]);
            }
        }

        printf("\n[1] Insert value on the stack\n[2] Remove last value from stack\n[3] Change exibition mode\n[4] Exit\nOption: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            if (!stackFull())
            {
                printf("Enter the value: ");
                scanf("%d", &value);

                push(value);
            }
            else
            {
                printf("Stack is full !!\n");
                system("pause");
            }

            break;
        }
        case 2:
        {
            if (!stackEmpty())
            {
                pop();
            }
            else
            {
                printf("Stack is empty !!\n");
                system("pause");
            }

            break;
        }
        case 3:
        {
            showStack = !showStack;
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