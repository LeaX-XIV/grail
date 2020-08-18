#include <stdlib.h>
#include <string.h>
#include "utils.h"

int max(int a, int b) {
	return a > b ? a : b;
	// return (a > b) * a + (a <= b) * b;
}

int min(int a, int b) {
	return a < b ? a : b;
	// return (a < b) * a + (a >= b) * b;
}

void shuffle_array(unsigned int* array, size_t size) {
	if(size > 1) {
		size_t i;
		for(i = 0; i < size - 1; ++i) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			if(j == i) continue;
			// int t = array[j];
			// array[j] = array[i];
			// array[i] = t;

			// array[i] ^= array[j];
			// array[j] ^= array[i];
			// array[i] ^= array[j];

			swap(&array[i], &array[j]);
		}
	}
}

void reverse_array(unsigned int* array, size_t size) {
	if(size > 1) {
		size_t i;
		for(i = 0; i < size / 2; ++i) {
			swap(&array[i], &array[size - 1 - i]);
		}
	}
}

void swap(unsigned int* a, unsigned int* b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}