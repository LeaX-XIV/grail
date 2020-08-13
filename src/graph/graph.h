//
//  graph.h
//  project
//
//  Created by 郭雅丹 on 2020/8/13.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>



#define MAX_LINE 100
enum {WHITE, GREY, BLACK};


typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
 
struct graph_s {
    vertex_t *g;
    unsigned int nv;
};

struct vertex_s {
    unsigned int id;
    int color;
    int dist;
    int disc_time;
    int endp_time;
    int pred;
    int scc;
    int *rowAdj;
};

struct edge_s {
    int weight;
    vertex_t *dst;
    edge_t *next;
};




graph_t* graph_load(char*);
void graph_attribute_init (graph_t*);
int graph_find(graph_t*,int);
void graph_dispose(graph_t*);






#endif /* graph_h */
