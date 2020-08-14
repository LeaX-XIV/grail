//
//  graph.c
//  project
//
//  Created by 郭雅丹 on 2020/8/13.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "../list/list.h"
#include "../interval/interval.h"

graph_t *graph_load(char *filename, int d) {
	graph_t *g;
	FILE *fp;
	unsigned int nodesnumber;
	unsigned int i;
	char child_string[10];
	unsigned int parent, child;

	g = malloc(sizeof(*g));
	if(g == NULL)
		return NULL;

	g->roots = list_create();

	fp = fopen(filename, "r");
	if(fp == NULL) {
		free(g);
		return NULL;
	}

	fscanf(fp, "%u", &nodesnumber);
	g->nv = nodesnumber;
	g->g = malloc(g->nv * sizeof(*g->g));
	if(g->g == NULL) {
		fclose(fp);
		free(g);
		return NULL;
	}

	if(graph_attribute_init(g, d) == 0) {	// Error
		fclose(fp);
		free(g);
		return NULL;
	}

	for(i = 0; i < nodesnumber; i++) {
		list_t *child_list = list_create();
		list_init(child_list, 1);

		fscanf(fp, "%u:", &parent);
		g->g[parent].id = parent;

		fscanf(fp, "%s", child_string);

		while(child_string[0] != '#') {
			child = atoi(child_string);
			if(list_append(child_list, child) == 0) // Save in list
				printf("Error\n"); 
			fscanf(fp, "%s", child_string);
		}

		g->g[i].rowAdj = child_list;
	}

	g->roots = graph_get_roots(g);

	fclose(fp);
	return g;
}

int graph_attribute_init(graph_t *g, int d) {
	int i, j, error = 0;
	for(i = 0; i < g->nv; i++) {
		g->g[i].id = i;
		g->g[i].color = WHITE;
		// g->g[i].disc_time = -1;
		// g->g[i].endp_time = -1;
		g->g[i].pred = -1;
		// g->g[i].rowAdj taken care with file read
		g->g[i].labels = malloc(d * sizeof(*g->g[i].labels));
		if(g->g[i].labels == NULL) {
			error = 1;
			break;
		}
	}

	for(j = 0; error == 1 && j < i; ++j) {
		free(g->g[j].labels);
	}

	return error == 0;
}

list_t* graph_get_roots(graph_t* graph) {
	int* indegree = calloc(graph->nv, sizeof(*indegree));
	int i, j;
	unsigned int v;
	list_t* roots = list_create();

	for(i = 0; i < graph->nv; ++i) {
		list_t* adj = graph->g[i].rowAdj;
		for(j = 0; j < list_length(adj); j++) {
			list_get(adj, j, &v);
			++indegree[v];
		}
	}

	list_init(roots, 1);
	for(i = 0; i < graph->nv; ++i) {
		if(indegree[i] == 0) {
			list_append(roots, i);
		}
	}

	return roots;
}

void graph_dispose(graph_t *g) {
	int i;
	for(i = 0; i < g->nv; i++) {
		free(g->g[i].rowAdj);
	}
	list_destroy(g->roots);
	free(g->roots);
	free(g->g);
	free(g);
	return;
}