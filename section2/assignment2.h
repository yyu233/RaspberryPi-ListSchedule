#ifndef _ASSIGNMENT2_BODY_
#define _ASSIGNMENT2_BODY_

#include "scheduler.h"

struct shared_variable; // Defined in assignment1.h

#define NUM_TASKS 8
#define ASAP 0
#define ALAP 1

int curTask;

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
    int outdeg[NUM_TASKS];
    int indeg[NUM_TASKS];
    int numEdges;
} GraphInfo;

int maxDepth;

//heap, remember to free
Queue* rootQ;
Queue sortedTasksASAP[NUM_TASKS];
Queue sortedTasksALAP[NUM_TASKS];
GraphInfo* gi;

int deps[NUM_TASKS][NUM_TASKS];
int asap[NUM_TASKS];
int alap[NUM_TASKS];

void enqueue(Queue* q, Node* node);

void dequeue(Queue* q);

void freeMem();

void bubbleSort (int arr [], int start, int end, long long workloadDeadlines[], int asap[], int alap[]);

void setCompleteSortedList(int completeSortedList[], Queue sortedTaskASAP [NUM_TASKS], 
                    long long workloadDeadlines[], int asap[], int alap[]);

void setGraphInfo(int workloadDependencies [NUM_TASKS][NUM_TASKS], GraphInfo* gi);

//void setupTopoSort(int mode);

void topologicalSort(int deps[NUM_TASKS][NUM_TASKS], GraphInfo* gi, Queue* rootQ, 
					Queue sortedTasks[NUM_TASKS], int levelTable[NUM_TASKS],int mode);

// Call at the start part of the program before actual scheduling
void learn_workloads(struct shared_variable* sv);

// Call in the scheduler thread
TaskSelection select_task(struct shared_variable* sv, const int* aliveTasks, long long idleTime);

#endif
