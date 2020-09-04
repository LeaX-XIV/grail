#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdlib.h>

typedef void* list_t;

// Malloc a new list
list_t* list_create();

// Initializes the list with initial_size cells: O(1)
int list_init(list_t* list, size_t initial_size);

// Appends value at the end of the list: O(n) in case of reallocation, O(1) otherwise
int list_append(list_t* list, unsigned int value);
// Inserts value in position pos: O(n)
int list_insert(list_t* list, unsigned int value, size_t pos);

// Get the index-th position and store in *value: O(1)
int list_get(list_t* list, size_t index, unsigned int* value);
// Get the last value and  store in *value: O(1)
int list_get_last(list_t* list, unsigned int* value);
// Returns 1 if value is contained in list, 0 otherwise: O(n)
int list_contains(list_t* list, unsigned int value);

// Removes index-th element from the list, and store in *value: O(n)
int list_remove(list_t* list, size_t index, unsigned int* value);
// Remove last element of the list and store in value: O(n) in case of reallocation, O(1) otherwise
int list_remove_last(list_t* list, unsigned int* value);

// Returns the length of the list: O(1)
int list_length(list_t* list);

// Returns the list as an array: O(n)
unsigned int* list_as_array(list_t* list);	// FREE IT YOURSELF!!!

// Frees the list
int list_destroy(list_t* list);

#endif // LIST_HEADER