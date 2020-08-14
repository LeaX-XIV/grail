#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdlib.h>

typedef void* list_t;

list_t* list_create();

int list_init(list_t* list, size_t initial_size);

int list_append(list_t* list, unsigned int value);
int list_insert(list_t* list, unsigned int value, size_t pos);

int list_get(list_t* list, size_t index, unsigned int* value);
int list_get_last(list_t* list, unsigned int* value);

int list_remove(list_t* list, size_t index, unsigned int* value);
int list_remove_last(list_t* list, unsigned int* value);

int list_length(list_t* list);

int list_destroy(list_t* list);

#endif // LIST_HEADER