#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "graph_p.h"
#include "../list/list.h"
#include "../interval/interval.h"
#include "../utils/utils.h"

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

	g->d = d;
	// g->roots = list_create();

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

	if(graph_attribute_init(g) == 0) {	// Error
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

	graph_randomized_labeling(g);

	fclose(fp);
	return g;
}

int graph_attribute_init(graph_t *g) {
	int i, j, error = 0;
	for(i = 0; i < g->nv; i++) {
		g->g[i].id = i;
		g->g[i].labels = calloc(g->d, sizeof(*g->g[i].labels));
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

	free(indegree);

	return roots;
}

void graph_dispose(graph_t *g) {
	int i, j;
	for(i = 0; i < g->nv; i++) {
		for(j = 0; j < g->d; ++j) {
			interval_destroy(g->g[i].labels[j]);
		}
		free(g->g[i].labels);
		list_destroy(g->g[i].rowAdj);
		free(g->g[i].rowAdj);
	}
	list_destroy(g->roots);
	free(g->roots);
	free(g->g);
	free(g);
	return;
}

void graph_randomized_labeling(graph_t* G) {
	pthread_t* threads = malloc(G->d * sizeof(*threads));
	alg1_t* params = malloc(G->d * sizeof(*params));
	// 3
	unsigned int* Roots = list_as_array(G->roots);
	int i;

	// 1
	for(i = 0; i < G->d; ++i) {
		params[i].i = i;
		// 2
		params[i].r = 1;
		params[i].G = G;
		// if(i % 2 == 0) {	// Randomized Pairs approach
			params[i].Roots = malloc(list_length(G->roots) * sizeof(*Roots));
			memcpy(params[i].Roots, Roots, list_length(G->roots) * sizeof(*Roots));
			shuffle_array(params[i].Roots, list_length(G->roots));
		// } else {
		// 	params[i].Roots = malloc(list_length(G->roots) * sizeof(*Roots));
		// 	memcpy(params[i].Roots, params[i-1].Roots, list_length(G->roots) * sizeof(*Roots));
		// 	reverse_array(params[i].Roots, list_length(G->roots));
		// }

		pthread_create(&threads[i], NULL, graph_random_visit_w, &params[i]);
	}

	free(Roots);

	for(i = 0; i < G->d; ++i) {
		pthread_join(threads[i], NULL);
		free(params[i].Roots);
	}
	free(params);
	free(threads);

	return;
}

void* graph_random_visit_w(void* arg) {
	int i = ((alg1_t*)arg)->i;
	int r = ((alg1_t*)arg)->r;
	graph_t* G = ((alg1_t*)arg)->G;
	unsigned int* Roots = ((alg1_t*)arg)->Roots; // Shuffled
	int j;

	// 4
	for(j = 0; j < list_length(G->roots); ++j) {
		// 5
		graph_random_visit(Roots[j], i, G, &r);
		// G->g[Roots[j]].color = BLACK;
	}

	return arg;
}

void graph_random_visit(unsigned int x, int i, graph_t* G, int* r) {
	// 6
	if(G->g[x].labels[i] != NULL) {
	// if(G->g[x].color == BLACK) {	// Already visited
		return;
	}

	// 7
	unsigned int* children_of_x = list_as_array(G->g[x].rowAdj);
	int n_children = list_length(G->g[x].rowAdj);
	int r_star_c = INT_MAX;
	int j;
	shuffle_array(children_of_x, n_children);
	for(j = 0; j < n_children; ++j) {
		unsigned int y = children_of_x[j];
		// 8
		graph_random_visit(y, i, G, r);
		// G->g[y].color = BLACK;
		// 9
		r_star_c = min(r_star_c, interval_first(G->g[y].labels[i]));
	}
	free(children_of_x);
	// 10
	G->g[x].labels[i] = interval_create(min(*r, r_star_c), *r);
	// 11
	++(*r);
}

int graph_reachable(graph_t* g, int u, int v) {
    for(int i=0;i<g->d;i++){
        if(interval_check(g->g[u].labels[i],g->g[v].labels[i]) == 0){
            return 0;
        }
        
    }
    
    if(list_contains(g->g[u].rowAdj, g->g[v].id)||g->g[u].id==g->g[v].id){
        return 1;
    }
    
    int s=list_length(g->g[u].rowAdj);

    for(int j=0;j<s;j++){
        unsigned int c;
        list_get(g->g[u].rowAdj, j, &c);
        if(graph_reachable(g, c, v) == 1) {
            return 1;
        } 
    }

    return 0;
}