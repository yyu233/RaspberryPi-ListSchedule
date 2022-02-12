#ifndef _TOPSORT_BODY_
#define _TOPSORT_BODY_

#define NUM_TASKS 8

typedef struct Node{
    int val;
    struct Node* next;
} Node;

typedef struct {
    int len;
    Node* head;
    Node* tail;
} Queue;

typedef struct {
    int indeg[NUM_TASKS];
    int numEdges;
} GraphInfo;


Queue sortedTasks[NUM_TASKS];
int asap[NUM_TASKS];
int alap[NUM_TASKS];

void enqueue(Queue* q, Node* node);

void dequeue(Queue* q);

void setGraphInfo(int workloadDependencies [NUM_TASKS][NUM_TASKS], GraphInfo* gi);

void topologicalSort(int* deps, GraphInfo* gi, Queue* sortedTasks, int* levelTable);

#endif