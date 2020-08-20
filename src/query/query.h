
#ifndef query_h
#define query_h

#include <stdio.h>
#include <pthread.h>

#include "../graph/graph.h"

struct file_data{
    graph_t *g;
    FILE *fp;
    pthread_mutex_t* mutex;
    int* results;
    int* i;
};

void* filereadthread(void *arg);

#endif /* query_h */
