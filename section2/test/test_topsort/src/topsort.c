#include <stdlib.h>
#include <stdio.h>

#include "topsort.h"

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
		//free memory
		printf("ERROR: dequeue empty queue \n");
		exit(-1);
	}
	q->len--;
	Node* tmp = q->head->next;
	free(q->head);
	q->head = tmp;
	if (q->len == 0) {
		q->tail = NULL;
	}
}

void setGraphInfo(int workloadDependencies[NUM_TASKS][NUM_TASKS], GraphInfo* gi) {
	int j = 0;
	for (; j < NUM_TASKS; j++) {
		//printf("Task: %d\n", j);
		int i = 0;
		for (; i < NUM_TASKS; i++) {
			//printf("workloadDependencies:[%d][%d] : %d\n", workloadDependencies[i][j]);
			gi->indeg[j] += workloadDependencies[i][j];
		}
		gi->numEdges += gi->indeg[j];
	}
}

// startNode  1D array
// deps 2D array
// output 1D array
void topologicalSort(int deps[NUM_TASKS][NUM_TASKS], GraphInfo* gi, Queue* rootQ, 
					Queue sortedTasks[NUM_TASKS], int levelTable[NUM_TASKS]) {
	//initialize rootQ
	int k = 0;
	for (; k < NUM_TASKS; k++) {
		if (gi->indeg[k] == 0) {
			Node* node = malloc(sizeof(Node));
			node->val = k;
			node->next = NULL;
			enqueue(rootQ, node);
		}
	}	
	//sort
	int i = 0;
	while (rootQ->len != 0) {
		//copy rootQ to sorted array
		Node* cur = rootQ->head;
		while (cur != NULL) {
			Node* elem = malloc(sizeof(Node));
			elem->val = cur->val;
			elem->next = NULL;
			enqueue(&sortedTasks[i], elem); 
			cur = cur->next;
		}
		//find next level of root
		int j = 0;
		int n = rootQ->len;
		for (; j < n; j++) {
			int u = rootQ->head->val;
			//set level
			levelTable[u] = i;
			//dequeue
			dequeue(rootQ);
			// search all nearest successors
			int v = 0;
			for (; v < NUM_TASKS; v++) {
				//find successor
				if (deps[u][v] == 1) {
					// remove edge
					deps[u][v] = 0;
					gi->indeg[v]--;
					gi->numEdges--;
					// no predecessor 
					if (gi->indeg[v] == 0) {
						//enqueue
						Node* node = malloc(sizeof(Node));
						node->val = v;
						node->next = NULL;
						enqueue(rootQ, node);
					}
				}
			}
		}
		i++;
	}
	if (gi->numEdges != 0) {
		//free memory
		Node* cur = rootQ->head;
		while (cur != NULL) {
			free(cur);
			cur = cur->next;
		}
		free(rootQ);
		exit(-1);
	}	
}