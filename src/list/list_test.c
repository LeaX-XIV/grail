#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main() {
	unsigned int v = 4;
	list_t* l = list_create();

	list_init(l, 1);

	list_append(l, 1);
	assert(list_get(l, 0, &v) == 1);
	printf("%u\n", v);
	assert(v == 1);
	assert(list_length(l) == 1);

	list_append(l, 37);
	assert(list_get(l, 0, &v) == 1);
	printf("%u", v);
	assert(v == 1);

	assert(list_get(l, 1, &v) == 1);
	printf("%u", v);
	assert(v == 37);
	assert(list_length(l) == 2);

	list_destroy(l);

	return 1;
}