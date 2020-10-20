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
    struct node *back;
} Node;



int main(){

    return 1;
}