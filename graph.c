#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"

Node *createNode(int dest)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->dest = dest;
    newNode->next = NULL;

    return newNode;
}

Graph *createGraph(int nodeNo)
{
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    newGraph->nodeNo = nodeNo;

    newGraph->array = (AdjList *)malloc(nodeNo * sizeof(AdjList));

    for (int i = 0; i < newGraph->nodeNo; i++)
        newGraph->array[i].head = NULL;

    return newGraph;
}

EdgeList *adjToEdge(Graph *graph)
{
    EdgeList *list = (EdgeList *)malloc(sizeof(EdgeList));
    list->edges = (Edge *)malloc(graph->nodeNo * (graph->nodeNo - 1) * sizeof(Edge));
    list->size = 0;

    AdjList *array = graph->array;

    int iterator = 0;
    for (int i = 0; i < graph->nodeNo; i++)
    {
        Node *curList = array->head;
        while (curList != NULL)
        {
            // if (curList->dest > iterator)
            // {
                list->edges[list->size].src = iterator;
                list->edges[list->size].dest = curList->dest;
                list->size += 1;
            // }
            curList = curList->next;
        }
        iterator++;
        array = array + 1;
    }

    return list;
}

EdgeList *kruskal(Graph *graph, EdgeList *eList, int *cost)
{

    EdgeList *list = (EdgeList *)malloc(sizeof(EdgeList));
    list->size = eList->size;
    list->edges = (Edge *)malloc(list->size * sizeof(Edge));

    memcpy(list->edges, eList->edges, eList->size * sizeof(Edge));

    // Sort edge list by weight
    for (int i = 0; i < list->size; i++)
    {
        for (int j = i+1; j < list->size; j++)
        {
            if (list->edges[i].weight > list->edges[j].weight)
            {
                Edge e = list->edges[i];
                list->edges[i] = list->edges[j];
                list->edges[j] = e;
            }
        }
    }

    *cost = 0;
    EdgeList *MST = (EdgeList *)malloc(sizeof(EdgeList));
    MST->edges = (Edge *)malloc(graph->nodeNo * sizeof(Edge));
    MST->size = 0;

    for (int i = 0; i < list->size && MST->size < graph->nodeNo; i++)
    {
        MST->edges[MST->size] = list->edges[i];
        MST->size++;

        if (isCycle(graph, MST) == 1)
            MST->size--;
        else
            *cost = *cost + MST->edges[MST->size-1].weight;
    }

    free(list);

    return MST;
}

int minKey(int *key, int *mstSet, int nodeNo)
{
    int min = INT_MAX;
    int minIndex;

    for (int i = 0; i < nodeNo; i++)
    {
        if (mstSet[i] == 0 && key[i] < min)
        {
            min = key[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void prim(Graph *graph)
{
    int *mstSet = (int *)calloc(graph->nodeNo, sizeof(int));
    int *key = (int *)malloc(graph->nodeNo * sizeof(int));
    for (int i = 0; i < graph->nodeNo; i++)
        key[i] = INT_MAX;
    int *parent = (int *)malloc(graph->nodeNo * sizeof(int));
    
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < graph->nodeNo - 1; i++)
    {
        int minV = minKey(key, mstSet, graph->nodeNo);

        mstSet[minV] = 1;

        while (graph->array[minV].head != NULL)
        {
            if (mstSet[graph->array[minV].head->dest] == 0 && graph->array[minV].head->weight < key[graph->array[minV].head->dest])
            {
                parent[graph->array[minV].head->dest] = minV;
                key[graph->array[minV].head->dest] = graph->array[minV].head->weight;
            }

            graph->array[minV].head = graph->array[minV].head->next;
        }
    }

    int totalCost = 0;
    for (int i = 1; i < graph->nodeNo; i++)
    {
        printf("(%d %d) -> cost %d\n", parent[i], i, key[i]);
        totalCost += key[i];
    }
    printf("Cost total: %d\n", totalCost);
}

void addEdgeUndirected(Graph *graph, int src, int dest)
{
    //First link
    Node *newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    //Second link
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void addEdgeDirected(Graph *graph, int src, int dest)
{
    Node *newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Prints adjacency list of a vertice
void printAdjList(Graph *graph, int node)
{
    Node *cursor = graph->array[node].head;

    printf("%d: ", node);
    while (cursor)
    {
        printf("%d ", cursor->dest);
        cursor = cursor->next;
    }
    
}

void BFS(Graph *graph, int startNode)
{
    int *visited = (int *)calloc(graph->nodeNo, sizeof(int));

    Queue *q = createQueue(graph->nodeNo);
    enqueue(q, startNode);
    visited[startNode] = 1;

    while (!isEmptyQueue(q))
    {
        int cur = dequeue(q);
        printf("Visited %d   ", cur);

        Node *cursor = graph->array[cur].head;
        while (cursor)
        {
            if (visited[cursor->dest] == 0)
            {
                enqueue(q, cursor->dest);
                visited[cursor->dest] = 1;
            }
            cursor = cursor->next;
        }
    }
}

void DFS(Graph *graph, int startNode)
{
    int *visited = (int *)calloc(graph->nodeNo, sizeof(int));

    Stack *s = createStack(graph->nodeNo);
    push(s, startNode);
    visited[startNode] = 1;

    while (!isEmptyStack(s))
    {
        int cur = pop(s);
        printf("Visited %d   ", cur);

        Node *cursor = graph->array[cur].head;
        while (cursor)
        {
            if (visited[cursor->dest] == 0)
            {
                push(s, cursor->dest);
                visited[cursor->dest] = 1;
            }
            cursor = cursor->next;
        }
    }
}

int isPath(Graph *graph, int src, int dest)
{
    int *visited = (int *)calloc(graph->nodeNo, sizeof(int));

    Stack *s = createStack(graph->nodeNo);
    push(s, src);
    visited[src] = 1;

    while (!isEmptyStack(s))
    {
        int cur = pop(s);

        Node *cursor = graph->array[cur].head;
        while (cursor)
        {
            if (cursor->dest == dest)
                return 1;

            if (visited[cursor->dest] == 0)
            {
                push(s, cursor->dest);
                visited[cursor->dest] = 1;
            }
            cursor = cursor->next;
        }
    }

    return 0;
}

int find(int parent[], int node)
{
    if (parent[node] == -1)
        return node;

    find(parent, parent[node]);
}

int isCycle(Graph *graph, EdgeList *list)
{
    int *parent = malloc(graph->nodeNo * sizeof(int));
    memset(parent, -1, graph->nodeNo * sizeof(int));
    for (int i = 0; i < list->size; i++)
    {
        int subset1 = find(parent, list->edges[i].src);
        int subset2 = find(parent, list->edges[i].dest);

        if (subset1 == subset2)
            return 1;

        parent[subset1] = subset2;
    }

    free(parent);

    return 0;
}