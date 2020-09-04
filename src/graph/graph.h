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
// n: number of nodes
// m: number of edges
// Load a graph from file to memory, initializing d labels per node: O(n * m)
graph_t* graph_load(char* filename, int d);
// Returns 1 if v is reachable from u in graph g using DFS: between O(d) and O(n + m)
int graph_reachable(graph_t* g, int u, int v);
// Returns the size of the structure in bytes: O(n)
size_t graph_size(graph_t* g);
// Frees the graph
void graph_dispose(graph_t* g);

#endif /* graph_h */
