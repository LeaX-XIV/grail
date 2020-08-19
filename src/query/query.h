
#ifndef query_h
#define query_h

#include "../graph/graph.h"
#include <stdio.h>
#include <pthread.h>

struct file_data{
    graph_t *g;
    FILE *fp;
    pthread_mutex_t* mutex;
};

struct thread_data{
    int u;
    int v;
    graph_t *g;
};

void* filereadthread(void *arg);
// int querythread(void *arg);
int query(int u,int v,graph_t*g);

#endif /* query_h */
