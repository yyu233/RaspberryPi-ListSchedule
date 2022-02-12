#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "topsort.h"

int main() {
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
    
    

    return 0;
}