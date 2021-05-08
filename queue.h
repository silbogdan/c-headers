#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueNode
{
    int value;
    struct queueNode *next;
} QueueNode;

typedef struct queue
{
    int capacity;
    int size;
    QueueNode *first, *last;
} Queue;

void showQueue(Queue *q);

Queue *createQueue(int capacity);

int isFullQueue(Queue *q);

int isEmptyQueue(Queue *q);

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

int peekQueue(Queue *q);

#endif