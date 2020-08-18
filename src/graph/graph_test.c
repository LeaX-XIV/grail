#include "graph.h"
#include "../list/list.h"
#include "../interval/interval.h"
#include <stdio.h>

int main() {
	int i, j;
	graph_t* g = graph_load("v100e10.gra", 3);
	unsigned int v = 5;
	// list_get(g->g[0].rowAdj, 0, &v);
	// printf("%u\n", v);

	printf("TESTING CHILDREN\n");
	for(i = 0; i < g->nv; ++i) {
		printf("%d: [ ", i);
		for(j = 0; j < list_length(g->g[i].rowAdj); ++j) {
			list_get(g->g[i].rowAdj, j, &v);
			printf("%u ", v);
		}
		printf(" ]\n");
	}

	printf("TESTING ROOTS\n");
	for(i = 0; i < list_length(g->roots); ++i) {
		list_get(g->roots, i, &v);
		printf("%u\n", v);
	}

	printf("TESTING LABELS\n");
	for(i = 0; i < g->nv; ++i) {
		interval_t* label1 = g->g[i].labels[0];
		interval_t* label2 = g->g[i].labels[1];
		interval_t* label3 = g->g[i].labels[2];
		printf("%d: [%d, %d] [%d, %d] [%d, %d] \n", i, interval_first(label1), interval_second(label1), interval_first(label2), interval_second(label2), interval_first(label3), interval_second(label3));
	}

	graph_dispose(g);
}