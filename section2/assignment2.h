#ifndef _ASSIGNMENT2_BODY_
#define _ASSIGNMENT2_BODY_

#include "scheduler.h"

typedef struct {
    int *buf;
    size_t len;
    size_t cap;
} ArrayList;

typedef struct {
    int val;
    Node* next;
} Node;

typedef struct {
    size_t len;
    Node* head;
    Node* tail;
} Queue;

typedef struct {
    int indeg[NUM_TASKS];
    int numEdges;
} GraphInfo;

NUM_TASKS;

Queue sortedTasks[NUM_TASKS];
int asap[NUM_TASKS];
int alap[NUM_TASKS];

struct shared_variable; // Defined in assignment1.h

void enqueue(Queue* q, Node* node);

void dequeue(Queue* q);

// Call at the start part of the program before actual scheduling
void learn_workloads(struct shared_variable* sv);

// Call in the scheduler thread
TaskSelection select_task(struct shared_variable* sv, const int* aliveTasks, long long idleTime);

void setGraphInfo(int* workloadDependencies, GraphInfo* gi);

void topologicalSort(int* deps, GraphInfo* gi, Queue* sortedTasks, int* levelTable);

#endif
