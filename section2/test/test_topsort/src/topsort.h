#ifndef _TOPSORT_BODY_
#define _TOPSORT_BODY_

#define NUM_TASKS 8
#define ASAP 0
#define ALAP 1

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
Queue sortedTasks[NUM_TASKS];
int completeSortedList[NUM_TASKS];

int asap[NUM_TASKS];
int alap[NUM_TASKS];

void enqueue(Queue* q, Node* node);

void dequeue(Queue* q);

void freeMem();

void bubbleSort (int arr [], int start, int end, long long workloadDeadlines[]);

void setCompleteSortedList(long long workloadDeadlines[]);

void setGraphInfo(int workloadDependencies [NUM_TASKS][NUM_TASKS], GraphInfo* gi);

void topologicalSort(int deps[NUM_TASKS][NUM_TASKS], GraphInfo* gi, Queue* rootQ, 
                    Queue sortedTasks[NUM_TASKS], int levelTable[NUM_TASKS], int mode);

#endif