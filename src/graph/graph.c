//
//  graph.c
//  project
//
//  Created by 郭雅丹 on 2020/8/13.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#include "graph.h"
#include "stdlib.h"
#include <stdio.h>
#include "limits.h"
#include "../list/list.h"

graph_t *graph_load (char *filename) {
    graph_t *g;
    char line[MAX_LINE];
    int weight, dir;
    FILE *fp;
    
    g = (graph_t *) calloc (1, sizeof(graph_t));
    fp = fopen (filename, "r");
    
    
    unsigned int nodesnumber;
    char child_string[10];
    unsigned int parent, child;
    
    fscanf(fp, "%u", &nodesnumber);
    g->nv = nodesnumber;
    g->g = (vertex_t *)
    calloc (g->nv, sizeof(vertex_t));
    
    graph_attribute_init (g);    //???where to init???
    
    int i=0,j=0;
    for(i=0;i<nodesnumber;i++){
        list_t* child_list = list_create();
        list_init(child_list, 1);

        fscanf(fp, "%u:", &parent);
         g->g[parent].id = parent;

        fscanf(fp, "%s", child_string);
        
        while(child_string[0] != '#') {
            child = atoi(child_string);
            if(list_append(child_list, child) == 0) printf("Error\n");    // Save in list
            fscanf(fp, "%s", child_string);
        }
    

        g->g[i].rowAdj = child_list;
    }
    
    fclose(fp);
    return g;
}


void graph_attribute_init (graph_t *g) {
    int i;
    for (i=0; i<g->nv; i++) {
        g->g[i].id=i;
        g->g[i].color = WHITE;
        g->g[i].dist = INT_MAX;
        g->g[i].disc_time = -1;
        g->g[i].endp_time = -1;
        g->g[i].pred = -1;
        g->g[i].scc = -1;
    }
    return;
}


int graph_find (graph_t *g, int id){
    int i;
for (i=0; i<g->nv; i++) {
    if (g->g[i].id == id) {
        return i;
    }
}
    return -1;
}

void graph_dispose (graph_t *g) {
    int i;
    for (i=0; i<g->nv; i++) {
        free(g->g[i].rowAdj);
    }
    free(g->g);
    free(g);
    return;
}