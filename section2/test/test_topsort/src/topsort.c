#include <stdlib.h>
#include <stdio.h>

#include "topsort.h"
#include "workload.h"

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

void freeMem() {
	    //free memory
		Node* cur = rootQ->head;
		while (cur != NULL) {
			Node* tmp = cur->next;
			free(cur);
			cur = tmp;
		}
		int i = 0;
		for (; i < NUM_TASKS; i++) {
			if (sortedTasks[i].len != 0) {
				cur = sortedTasks[i].head;
				while (cur != NULL) {
					Node* tmp = cur->next;
					free(cur);
					cur = tmp;
				}
			}
		}
		free(rootQ);
}


void bubbleSort (int arr [], int start, int end, long long workloadDeadlines[]) {
	int i = start;
	for (; i < end - 1; i++) {
		int j = start;
		for (; j < end - i - 1; j++) {
			// mobility 
			int curMob= alap[j] - asap[j];
			int nextMob = alap[j + 1] - asap[j]; 
			if (curMob > nextMob) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp; 
			}
			// EDF
			if (curMob == nextMob) {
				if (workloadDeadlines[j] > workloadDeadlines[j + 1]) {
					int tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}
	}
}

void setCompleteSortedList(long long workloadDeadlines[]) {
	int i = 0;
	int j = 0;
	int start = 0;
	for (; i < NUM_TASKS; i++) {
		if (sortedTasks[i].len == 0) {
			break;
		}
		Node* cur = sortedTasks[i].head;
		while (cur != NULL) {
			completeSortedList[j] = cur->val;
			j++;
			cur = cur->next;
		}
		bubbleSort(completeSortedList, start, j, workloadDeadlines);
		start = j;
	}
}

void setGraphInfo(int workloadDependencies[NUM_TASKS][NUM_TASKS], GraphInfo* gi) {
	int j = 0;
	//set indegree and edges
	for (; j < NUM_TASKS; j++) {
		int i = 0;
		for (; i < NUM_TASKS; i++) {
			gi->indeg[j] += workloadDependencies[i][j];
		}
		gi->numEdges += gi->indeg[j];
	}
	//set outdegree
	int i = 0;
	for (; i < NUM_TASKS; i++) {
		j = 0;
		for (; j <NUM_TASKS; j++) {
			gi->outdeg[i] += workloadDependencies[i][j];
		}
	}
}

// startNode  1D array
// deps 2D array
// output 1D array
void topologicalSort(int deps[NUM_TASKS][NUM_TASKS], GraphInfo* gi, Queue* rootQ, 
					Queue sortedTasks[NUM_TASKS], int levelTable[NUM_TASKS], int mode) {
	//initialize rootQ
	int k = 0;
	if (mode == ASAP) {
		for (; k < NUM_TASKS; k++) {
			if (gi->indeg[k] == 0) {
				Node* node = malloc(sizeof(Node));
				node->val = k;
				node->next = NULL;
				enqueue(rootQ, node);
			}
		}
	}
	if (mode == ALAP) {
		for (; k < NUM_TASKS; k++) {
			if (gi->outdeg[k] == 0) {
				Node* node = malloc(sizeof(Node));
				node->val = k;
				node->next = NULL;
				enqueue(rootQ, node);
			}
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
			if (mode == ASAP) {
				levelTable[u] = i;
			}
			if (mode == ALAP) {
				levelTable[u] = maxDepth - i;
			}
			//dequeue
			dequeue(rootQ);
			if (mode == ASAP) {
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
			if (mode == ALAP) {
				// search all nearest predecessor
				int v = 0;
				for (; v < NUM_TASKS; v++) {
					//find predecessor
					if (deps[v][u] == 1) {
						// remove edge
						deps[v][u] = 0;
						gi->outdeg[v]--;
						gi->numEdges--;
						// no successor 
						if (gi->outdeg[v] == 0) {
							//enqueue
							Node* node = malloc(sizeof(Node));
							node->val = v;
							node->next = NULL;
							enqueue(rootQ, node);
						}
					}
				}
			}
		}
		i++;
	}
	if (mode == ASAP) {
		maxDepth = i - 1;
	}
	if (gi->numEdges != 0) {
		//free memory
		Node* cur = rootQ->head;
		while (cur != NULL) {
			Node* tmp = cur->next;
			free(cur);
			cur = tmp;
		}
		int i = 0;
		for (; i < NUM_TASKS; i++) {
			if (sortedTasks[i].len != 0) {
				cur = sortedTasks[i].head;
				while (cur != NULL) {
					Node* tmp = cur->next;
					free(cur);
					cur = tmp;
				}
			}
		}
		free(rootQ);
		exit(-1);
	}	
}
