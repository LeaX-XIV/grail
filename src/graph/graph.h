//
//  graph.h
//  project
//
//  Created by 郭雅丹 on 2020/8/13.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//
#include "../list/list.h"
#include "../interval/interval.h"

#ifndef graph_h
#define graph_h

typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;

struct vertex_s {
    unsigned int id;
    list_t* rowAdj;
    interval_t** labels;
};

struct graph_s {
    vertex_t *g;
    unsigned int nv;
    list_t* roots;
    int d;
};

graph_t* graph_load(char*, int);
int graph_reachable(graph_t* g, int u, int v);
void graph_dispose(graph_t*);

#endif /* graph_h */
