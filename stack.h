#ifndef STACK_H
#define STACK_H

typedef struct stack
{
    int top;
    int capacity;
    int *array;
} Stack;

void showStack(Stack *stk);

Stack* createStack(int capacity);

int isFullStack(Stack *stk);

int isEmptyStack(Stack *stk);

void push(Stack *stk, int value);

int pop(Stack *stk);

int peekStack(Stack *stk);

#endif