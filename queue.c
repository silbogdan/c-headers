#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void showQueue(Queue *q)
{
    QueueNode *nodeCopy = q->first;
    while (nodeCopy != NULL)
    {
        printf("%d ", nodeCopy->value);
        nodeCopy = nodeCopy->next;
    }
}

Queue *createQueue(int capacity)
{
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->capacity = capacity;
    newQueue->size = 0;
    newQueue->first = NULL;
    newQueue->last = NULL;
}

int isFullQueue(Queue *q)
{
    return q->size >= q->capacity;
}

int isEmptyQueue(Queue *q)
{
    return q->first == NULL;
}

void enqueue(Queue *q, int value)
{
    if (isFullQueue(q))
        return;

    q->size++;

    QueueNode *qNode = (QueueNode *)malloc(sizeof(QueueNode));
    qNode->value = value;
    qNode->next = NULL;

    if (q->first == NULL)
    {
        q->first = qNode;
        q->last = qNode;
    }
    else
    {
        q->last->next = qNode;
        q->last = q->last->next;
    }
}

int dequeue(Queue *q)
{
    if (isEmptyQueue(q))
        return -1; // Normally some error

    int value = q->first->value;
    QueueNode *temp = q->first;
    q->first = q->first->next;
    q->size--;
    free(temp);

    return value;
}

int peekQueue(Queue *q)
{
    if (isEmptyQueue(q))
        return -1; // Normally some error

    return q->first->value;
}