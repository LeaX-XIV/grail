#include "graph.h"
#include "../list/list.h"
#include <stdio.h>

int main() {
	graph_t* g = graph_load("v100e10.gra", 1);
	unsigned int v = 5;
	list_get(g->g[0].rowAdj, 0, &v);
	printf("%u\n", v);
	int i;
	for(i = 0; i < list_length(g->roots); ++i) {
		list_get(g->roots, i, &v);
		printf("%u\n", v);
	}
}