#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void showStack(Stack *stk)
{
    for (int i = 0; i <= stk->top; i++)
        printf("%d ", stk->array[i]);
}

Stack* createStack(int capacity)
{
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->top = -1;
    stk->capacity = capacity;
    stk->array = (int *)malloc(capacity * sizeof(int));
}

int isFullStack(Stack *stk) // No pun intended
{
    return stk->top == stk->capacity - 1;
}

int isEmptyStack(Stack *stk)
{
    return stk->top == -1;
}

void push(Stack *stk, int value)
{
    if (isFullStack(stk))
        return;
        
    stk->array[++(stk->top)] = value;
}

int pop(Stack *stk)
{
    if (isEmptyStack(stk))
        return -1; // Normally some error

    return stk->array[(stk->top)--];
}

int peekStack(Stack *stk)
{
    if (isEmptyStack(stk))
        return -1; // Normally some error
    
    return stk->array[(stk->top)];
}