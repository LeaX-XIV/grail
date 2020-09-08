#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utils.h"

int main() {

	srand(time(NULL));

	int i, j;
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int* b = malloc(10 * sizeof(*b));

	for(i = 0; i < 10; ++i) {
		memcpy(b, a, 10 * sizeof(*b));
		shuffle_array((unsigned int*) b, 10);
		for(j = 0; j < 10; ++j) {
			printf("%d ", b[j]);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;

}