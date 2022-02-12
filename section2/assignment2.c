#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void enqueue(Queue* q, Node* node) {
	if (q->len == 0) {
		q->head = node;
	} else {
		q->tail->next = node;
	}
	q->tail = node;
	q->len++;
}

void dequeue(Queue* q) {
	if (q->len == 0) {
		printDBG("ERROR: dequeue empty queue \n");
		exit(-1);
	}
	q->len--;
	Node* tmp = q->head->next;
	q->head->next = NULL;
	q->head = tmp;
	if (q->len == 0) {
		q->tail = NULL;
	}
}

void setGraphInfo(int* workloadDependencies, GraphInfo* gi) {
	int i = 0;
	int j = 0;
	for (; j < NUM_TASKS; j++) {
		for (; i < NUM_TASKS; i++) {
			gi->indeg[j] += workloadDependencies[i * NUM_TASKS + j];
		}
		gi->numEdges += gi->indeg[j];
	}
}

// startNode  1D array
// deps 2D array
// output 1D array
void topologicalSort(int* deps, GraphInfo* gi, Queue* sortedTasks, int* levelTable) {
	Queue rootQ = {.len = 0, .head = NULL, .tail = NULL};
	//initialize rootQ
	int k = 0;
	for (; k < NUM_TASKS; k++) {
		if (gi->indeg[k] == 0) {
			Node node = {.val = k, .next = NULL};
			enqueue(&rootQ, &node);
		}
	}

	//sort
	int i = 0;
	while (rootQ.len != 0) {
		//insert rootQ to sorted array
		sortedTasks[i] = rootQ;
		//find next level of root
		int j = 0;
		int n = rootQ.len;
		for (; j < n; j++) {
			int u = rootQ.head->val;
			//set level
			levelTable[u] = i;
			//dequeue
			dequeue(&rootQ);
			// search all nearest successors
			int v = 0;
			for (; v < NUM_TASKS; v++) {
				//find successor
				if (deps[u * NUM_TASKS + v] == 1) {
					// remove edge
					deps[u * NUM_TASKS + v] == 0;
					gi->indeg[v]--;
					gi->numEdges--;
					// no predecessor 
					if (gi->indeg[v] == 0) {
						//enqueue
						Node node = {.val = v, .next = NULL};
						enqueue(&rootQ, &node);
					}
				}
			}
		}
		i++;
	}

	if (gi->numEdges != 0) {
		printDBG("ERROR: graph contains cycle\n");
		exit(-1);
	}	
}

void newArrayList(ArrayList* arr, size_t cap) {
    arr->buf = malloc(cap * sizeof(int));
	arr->len = 0;
	arr->cap = cap;
}

void arrayListAdd(ArrayList* arr, int val) {
	if (arr->len == arr->cap) {
		arr->cap *= 2;
		arr->buf = realloc(arr->buf, arr->cap * sizeof(int));
	}
	arr->buf[arr->len++] = val;
}

// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]
// The same for workload dependencies which is defined in the "workloadDependencies" variable
// See also deadlines.c and workload.h

// Assignment: You need to implement the following two functions.

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters

// sv: The variable which is shared for every function over all threads
void learn_workloads(SharedVariable* v) {
	// TODO: Fill the body
	// This function is executed before the scheduling simulation.
	// You need to calculate the execution time of each thread here.
	//
	// Thread functions: 
	// thread_button, thread_big, thread_encoder, thread_obstacle,
	// thread_twocolor, thread_rgbcolor, thread_aled, thread_buzzer

	// 1. asap

	// 2. alap

	// 3. mobility = alap - asap

	// Tip 1. You can call each workload function here like:
	// thread_button();

	// Tip 2. You can get the current time here like:
	// long long curTime = get_current_time_us();
}


// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reach the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable* sv, const int* aliveTasks, long long idleTime) {
	// TODO: Fill the body
	// This function is executed inside of the scheduling simulation.
    // You need to implement a list scheduler.

    // Goal: Select a task that
    //      - Satisfy the dependencies
    //      - Has the highest priority (min mobility)
    //      - If multiple tasks have the same priority, pick the one with the earliest deadline

	// Tip 1. You may get the current time elapsed in the scheduler here like:
	// long long curTime = get_scheduler_elapsed_time_us();

	// Also, do not make any interruptable / IO tasks in this function.
	// You can use printfDBG instead of printf.

	// Sample scheduler: Round robin
	// It selects a next thread using aliveTasks.
	/*static int prev_selection = -1;

	int i = prev_selection + 1;
	while(1) {
		if (i == NUM_TASKS)
			i = 0;

		if (aliveTasks[i] == 1) {
			prev_selection = i;
			break;
		}
		++i;
	}*/

	
	// 4. schedule

	// The retun value can be specified like this:
	TaskSelection sel;
	//sel.task = prev_selection; // The thread ID which will be scheduled. i.e., 0(BUTTON) ~ 7(BUZZER)
	sel.freq = 1; // Request the maximum frequency (if you want the minimum frequency, use 0 instead.)

    return sel;
}






