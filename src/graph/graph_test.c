#include "graph.h"
#include "../list/list.h"
#include <stdio.h>

int main() {
	graph_t* g = graph_load("src/graph/simple_graph.gra");
	unsigned int v = 5;
	list_get(g->g[0].rowAdj, 0, &v);
	printf("%u\n", v);
}