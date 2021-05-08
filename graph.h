#ifndef GRAPH_H
#define GRAPH_H

typedef struct node
{
    int dest, weight;
    struct node *next;
    
} Node;

typedef struct adjList
{
    Node *head;
} AdjList;

typedef struct graph
{
    int nodeNo;
    AdjList *array;
} Graph;

typedef struct edge
{
    int src, dest, weight;
} Edge;

typedef struct edgeList
{
    int size;
    Edge *edges;
} EdgeList;

Node *createNode(int dest);

Graph *createGraph(int nodeNo);

EdgeList *adjToEdge(Graph *graph);

EdgeList* kruskal(Graph *graph, EdgeList *eList, int *cost);

void prim(Graph *graph);

void addEdgeUndirected(Graph *graph, int src, int dest);

void addEdgeDirected(Graph *graph, int src, int dest);

void printAdjList(Graph *graph, int node);

void BFS(Graph *graph, int startNode);

void DFS(Graph *graph, int startNode);

int isPath(Graph *graph, int src, int dest);

int isCycle(Graph *graph, EdgeList *list);
#endif