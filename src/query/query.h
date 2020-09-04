
#ifndef query_h
#define query_h

#include <stdio.h>
#include <pthread.h>

#include "../graph/graph.h"

struct alg2{
    graph_t *g;
    FILE *fp;
    pthread_mutex_t* mutex;
    char* results;
    int* i;
};

// Read a line from file pointed by arg until EOF, and for every line checks if the couple of nodes are reachable
void* filereadthread(void *arg);

#endif /* query_h */
