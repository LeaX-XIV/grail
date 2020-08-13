#include "list.h"

#ifndef LIST_PRIVATE_HEADER
#define LIST_PRIVATE_HEADER

struct list {
	unsigned int* arr;
	size_t size; 
	size_t head;
};

typedef struct list list_pt;

int list_realloc(list_pt* list, size_t new_size);

#endif // LIST_PRIVATE_HEADER