#include <pthread.h>

#include "../list/list.h"
#include "graph.h"

#ifndef GRAPH_PRIVATE_HEADER
#define GRAPH_PRIVATE_HEADER

struct alg1 {
	int i;
	int r;
	graph_t* G;
	unsigned int* Roots; // Shuffled
};

typedef struct alg1 alg1_t;

int graph_attribute_init (graph_t*);
list_t* graph_get_roots(graph_t*);

void graph_randomized_labeling(graph_t* g);
void* graph_random_visit_w(void* arg);
void graph_random_visit(unsigned int x, int i, graph_t* G, int* r);

#endif // GRAPH_PRIVATE_HEADER