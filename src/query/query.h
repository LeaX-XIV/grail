
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
    int d;
};

void* filereadthread(void *arg);
void* querythread(void *arg);
int query(int u,int v,graph_t*g,int d);

#endif /* query_h */
