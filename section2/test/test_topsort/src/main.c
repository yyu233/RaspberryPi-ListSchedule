#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "topsort.h"

void test_setGraphInfo() {
    int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);
    int i = 0;
    for (; i < NUM_TASKS; i++) {
        printf("indegree of %d : %d\n", i, gi.indeg[i]);
    }
    
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 1);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 1);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 1);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 0);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 2);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 5);

    printf("PASSED: test_setGraphInfo\n");
}

void test_setGraphInfo_2() {
    int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);
    int i = 0;
    for (; i < NUM_TASKS; i++) {
        printf("indegree of %d : %d\n", i, gi.indeg[i]);
    }
    
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 1);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 0);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 0);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 1);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 1);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 3);

    printf("PASSED: test_setGraphInfo_2\n");
}

void test_setGraphInfo_3() {
    int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);
    int i = 0;
    for (; i < NUM_TASKS; i++) {
        printf("indegree of %d : %d\n", i, gi.indeg[i]);
    }
    
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 0);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 0);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 2);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 0);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 1);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 3);

    printf("PASSED: test_setGraphInfo_3\n");
}

void test_queue() {
   /** Node n1 = {.val = 0, .next = NULL};
    Node n2 = {.val = 1, .next = NULL};
    Node n3 = {.val = 2, .next = NULL};
    **/

    Node* n1 = malloc(sizeof(Node));
    n1->val = 0;
    n1->next = NULL;
    Node* n2 = malloc(sizeof(Node));
    n2->val = 1;
    n2->next = NULL;
    Node* n3 = malloc(sizeof(Node));
    n3->val = 0;
    n3->next = NULL;
    Queue q = {.head = NULL, .len = 0, .tail = NULL};

    enqueue(&q, n1);
    printf("head: %d  tail: %d len: %d\n", q.head->val, q.tail->val, q.len);
    assert(q.head->val == n1->val);
    assert(q.tail->val == n1->val);
    assert(q.len == 1);

    enqueue(&q, n2);
    printf("head: %d  tail: %d len: %d\n", q.head->val, q.tail->val, q.len);
    assert(q.head->val == n1->val);
    assert(q.tail->val == n2->val);
    assert(q.len == 2);

    enqueue(&q, n3);
    printf("head: %d  tail: %d len: %d\n", q.head->val, q.tail->val, q.len);
    assert(q.head->val == n1->val);
    assert(q.tail->val == n3->val);
    assert(q.len == 3);


    dequeue(&q);
    printf("head: %d  tail: %d len: %d\n", q.head->val, q.tail->val, q.len);
    assert(q.head->val == n2->val);
    assert(q.tail->val == n3->val);
    assert(q.len == 2);

    dequeue(&q);
    printf("head: %d  tail: %d len: %d\n", q.head->val, q.tail->val, q.len);
    assert(q.head->val == n3->val);
    assert(q.tail->val == n3->val);
    assert(q.len == 1);

    dequeue(&q);
    printf("head: %s  tail: %s len: %d\n", q.head, q.tail, q.len);
    assert(q.head == NULL);
    assert(q.tail == NULL);
    assert(q.len == 0);

    dequeue(&q);
    
}

void test_topologicalsort() {
    int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);

    rootQ = malloc(sizeof(Queue));
    rootQ->head=NULL;
    rootQ->len=0;
    rootQ->tail=NULL;

    Queue sortedTasks[NUM_TASKS] = {{.head = NULL, .len=0, .tail = NULL}};

    int levelTable[NUM_TASKS] = {0};

    topologicalSort(deps, &gi, rootQ, sortedTasks, levelTable);
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 0);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 0);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 0);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 0);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 0);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 0);


    printf("levels of sortedTasks should be : %d\n", 3);
    assert(sortedTasks[0].len != 0 && sortedTasks[1].len != 0 &&
          sortedTasks[2].len != 0);
    assert(sortedTasks[3].len == 0 && sortedTasks[4].len == 0 &&
          sortedTasks[5].len == 0 && sortedTasks[6].len == 0 &&
          sortedTasks[7].len == 0 && sortedTasks[8].len == 0);

    printf("Number of first level of sorted Tasks got: %d\n", sortedTasks[0].len);
    assert(sortedTasks[0].len == 4);

    int i = 0;
    Node* cur = sortedTasks[0].head;
    for (; i < sortedTasks[0].len; i++) {
        printf("first level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }
    

    printf("Number of second level of sorted Tasks got: %d\n", sortedTasks[1].len);
    assert(sortedTasks[1].len == 3);

    i = 0;
    cur = sortedTasks[1].head;
    for (; i < sortedTasks[1].len; i++) {
        printf("second level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }

    printf("Number of third level of sorted Tasks got: %d\n", sortedTasks[2].len);
    assert(sortedTasks[2].len == 1);

    i = 0;
    cur = sortedTasks[2].head;
    for (; i < sortedTasks[2].len; i++) {
        printf("third level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }

    printf("PASSED: test_topologicalsort\n");

    cur = rootQ->head;
    while (cur != NULL) {
        Node* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    i = 0;
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

void test_topologicalsort_2() {
    int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    
    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);
    rootQ = malloc(sizeof(Queue));
    rootQ->head=NULL;
    rootQ->len=0;
    rootQ->tail=NULL;

    Queue sortedTasks[NUM_TASKS] = {{.head = NULL, .len=0, .tail = NULL}};

    int levelTable[NUM_TASKS] = {0};
    
    topologicalSort(deps, &gi, rootQ, sortedTasks, levelTable);
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 0);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 0);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 0);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 0);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 0);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 0);


    printf("levels of sortedTasks should be : %d\n", 3);
    assert(sortedTasks[0].len != 0 && sortedTasks[1].len != 0 &&
          sortedTasks[2].len != 0);
    assert(sortedTasks[3].len == 0 && sortedTasks[4].len == 0 &&
          sortedTasks[5].len == 0 && sortedTasks[6].len == 0 &&
          sortedTasks[7].len == 0 && sortedTasks[8].len == 0);

    printf("Number of first level of sorted Tasks got: %d\n", sortedTasks[0].len);
    assert(sortedTasks[0].len == 5);

    int i = 0;
    Node* cur = sortedTasks[0].head;
    for (; i < sortedTasks[0].len; i++) {
        printf("first level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }
    

    printf("Number of second level of sorted Tasks got: %d\n", sortedTasks[1].len);
    assert(sortedTasks[1].len == 2);

    i = 0;
    cur = sortedTasks[1].head;
    for (; i < sortedTasks[1].len; i++) {
        printf("second level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }

    printf("Number of third level of sorted Tasks got: %d\n", sortedTasks[2].len);
    assert(sortedTasks[2].len == 1);

    i = 0;
    cur = sortedTasks[2].head;
    for (; i < sortedTasks[2].len; i++) {
        printf("third level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }

    printf("PASSED: test_topologicalsort_2\n");
    
}

void test_topologicalsort_3() {
   int workloadDependencies[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    int deps[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    GraphInfo gi = {.indeg = {0, 0, 0, 0, 0, 0, 0, 0}, .numEdges = 0};
    setGraphInfo(workloadDependencies, &gi);

    rootQ = malloc(sizeof(Queue));
    rootQ->head=NULL;
    rootQ->len=0;
    rootQ->tail=NULL;

    Queue sortedTasks[NUM_TASKS] = {{.head = NULL, .len=0, .tail = NULL}};

    int levelTable[NUM_TASKS] = {0};

    topologicalSort(deps, &gi, rootQ, sortedTasks, levelTable);
    printf("indegree of %d: %d\n", 0, gi.indeg[0]);
    assert(gi.indeg[0] == 0);
    
    printf("indegree of %d: %d\n", 1, gi.indeg[1]);
    assert(gi.indeg[1] == 0);
        
    printf("indegree of %d: %d\n", 2, gi.indeg[2]);
    assert(gi.indeg[2] == 0);
    
    printf("indegree of %d: %d\n", 3, gi.indeg[3]);
    assert(gi.indeg[3] == 0);
    
    printf("indegree of %d: %d\n", 4, gi.indeg[4]);
    assert(gi.indeg[4] == 0);

    printf("indegree of %d: %d\n", 5, gi.indeg[5]);
    assert(gi.indeg[5] == 0);

    printf("indegree of %d: %d\n", 6, gi.indeg[6]);
    assert(gi.indeg[6] == 0);

    printf("indegree of %d: %d\n", 7, gi.indeg[7]);
    assert(gi.indeg[7] == 0);
    
    printf("number of edges: %d\n", gi.numEdges);
    assert(gi.numEdges == 0);


    printf("levels of sortedTasks should be : %d\n", 2);
    assert(sortedTasks[0].len != 0 && sortedTasks[1].len != 0 );
    assert(sortedTasks[2].len == 0 &&sortedTasks[3].len == 0 && sortedTasks[4].len == 0 &&
          sortedTasks[5].len == 0 && sortedTasks[6].len == 0 &&
          sortedTasks[7].len == 0 && sortedTasks[8].len == 0);

    printf("Number of first level of sorted Tasks got: %d\n", sortedTasks[0].len);
    assert(sortedTasks[0].len == 6);

    int i = 0;
    Node* cur = sortedTasks[0].head;
    for (; i < sortedTasks[0].len; i++) {
        printf("first level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }
    

    printf("Number of second level of sorted Tasks got: %d\n", sortedTasks[1].len);
    assert(sortedTasks[1].len == 2);

    i = 0;
    cur = sortedTasks[1].head;
    for (; i < sortedTasks[1].len; i++) {
        printf("second level of sorted Tasks got: %d\n", cur->val);
        cur = cur->next;
    }

    
    printf("PASSED: test_topologicalsort_3\n");

    cur = rootQ->head;
    while (cur != NULL) {
        Node* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    i = 0;
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

int main() {
    test_setGraphInfo();
    test_setGraphInfo_2();
    test_setGraphInfo_3();
    test_topologicalsort();
    test_topologicalsort_2();
    test_topologicalsort_3();
    //test_queue();
    return 0;
}