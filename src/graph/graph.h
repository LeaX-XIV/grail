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




enum {WHITE, GREY, BLACK};


typedef struct graph_s graph_t;
typedef struct vertex_s vertex_t;
 
struct graph_s {
    vertex_t *g;
    unsigned int nv;
    list_t* roots;
};

struct vertex_s {
    unsigned int id;
    int color;
    // int discovery_time;
    // int end_time;
    int pred;
    list_t* rowAdj;
    interval_t* labels;
};




graph_t* graph_load(char*, int);
int graph_attribute_init (graph_t*, int);
list_t* graph_get_roots(graph_t*);
void graph_dispose(graph_t*);






#endif /* graph_h */
