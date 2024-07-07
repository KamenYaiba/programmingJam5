#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int value;
} Node;


typedef struct MinQueue
{
    int size;
    Node *firstNode;
    Node *lastNode;
}MinQueue;

int compare(const void* a, const void* b);
MinQueue* newMinQueue(int *array, int n);
void printQueue(MinQueue *mq);
void insert(MinQueue *mq, int v);
int pop(MinQueue *mq);
int minWeldingCost(int *bars, int n);


//page 17 in the PDF
int main()
{
    int n = 10;
    int rods[] = {56, 15, 35, 86, 23, 48, 52, 25, 65, 74};
    printf("%d", minWeldingCost(rods, n)); //output: 1535
}


int minWeldingCost(int *rods, int n)
{
    MinQueue* mq = newMinQueue(rods, n);
    int cost = 0;
    int newRod;
    while(mq->size > 1)
    {
        newRod = pop(mq) + pop(mq);
        insert(mq, newRod);
        cost+= newRod;
    }
    free(mq);
    mq = NULL;
    return cost;
}


MinQueue* newMinQueue(int *array, int n)
{
    qsort(array, n, sizeof(int), compare);
    MinQueue *mq = (MinQueue*) malloc(sizeof(MinQueue));
    Node *preNode = (Node*) malloc(sizeof(Node));;
    preNode->value = array[0];
    preNode->next = NULL;
    mq->firstNode = preNode;
    mq->size = n;

    Node *newNode;
    for(int i = 1; i < n; i++)
    {
        newNode = (Node*) malloc(sizeof(Node));
        newNode->value = array[i];
        newNode->next = NULL;
        preNode->next = newNode;
        preNode = newNode;
    }
    mq->lastNode = preNode;
    return mq;
}


void insert(MinQueue *mq, int v)
{
    Node *node = mq->firstNode;
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->value = v;
    newNode->next = NULL;
    mq->size++;

    if(mq->size == 1)
    {
        mq->firstNode = newNode;
        return;
    }
    
    if(v < node->value)
    {
        newNode->next = node;
        mq->firstNode = newNode;
        return;
    }

    if(v > mq->lastNode->value)
    {
        mq->lastNode->next = newNode;
        mq->lastNode = newNode;
        return;
    }
    
    do
    {
        if(!(v < node->value) && !(v > node->next->value)) break;
        node = node->next;
    } while (node->next->next != NULL);
    
    Node *temp = node->next;
    node->next = newNode;
    newNode->next = temp;
}


int pop(MinQueue *mq)
{
    if(mq->size == 0)
    {
        return -1;
    } 

    Node *node = mq->firstNode;
    mq->firstNode = node->next;
    int res = node->value;
    free(node);
    mq->size--;
    return res;
}


int compare(const void* a, const void* b)
{
    int n1 = *((int*)a), n2 = *((int*)b);
    return (n1 > n2) - (n1 < n2);
}



void printQueue(MinQueue *mq)
{
    if(mq == NULL) return;

    Node *node = mq->firstNode;
    int n = mq->size;

    for(int i = 0; i < n; i++)
    {
        printf("%d  ", node->value);
        node = node->next;
    }
    printf("\n");
}
