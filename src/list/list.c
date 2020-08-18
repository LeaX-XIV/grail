#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_p.h"

list_t* list_create() {
	list_t* list = malloc(sizeof(list_pt));

	return list;
}

int list_init(list_t* list, size_t initial_size) {
	unsigned int* placeholder_arr;
	list_pt* list_p;

	if(list != NULL) {
		list_p = (list_pt*) list;

		placeholder_arr = malloc(initial_size * (sizeof *(list_p->arr)));
		if(placeholder_arr == NULL) {
			list_p->arr = NULL;
			list_p->size = 0;
			list_p->head = 0;
			return 0;
		}
		list_p->arr = placeholder_arr;
		list_p->size = initial_size;
		list_p->head = 0;

		return 1;
	}

	return 0;
}

int list_append(list_t* list, unsigned int value) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(list_p->head >= list_p->size) { // Array is full, need reallocation O(n)
			if(list_realloc(list_p, list_p->size * 2 + 1) == 0) {
				return 0;
			}
		}

		list_p->arr[list_p->head] = value;
		(list_p->head)++;
		return 1;
	}

	return 0;
}

int list_insert(list_t* list, unsigned int value, size_t pos) {
	int i;
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(pos > list_p->head) return 0;

		if(list_p->head >= list_p->size) { // Array is full, need reallocation O(n)
			if(list_realloc(list_p, list_p->size * 2 + 1) == 0) {
				return 0;
			}
		}

		for(i = list_p->head; i > pos; --i) {
			list_p->arr[i] = list_p->arr[i-1];
		}
		list_p->arr[pos] = value;
		++(list_p->head);

		return 1;
	}

	return 0;
}

int list_get(list_t* list, size_t index, unsigned int* value) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(value == NULL) return 0;
		if(index > list_p->head) return 0;

		*value = list_p->arr[index];

		return 1;
	}

	return 0;
}

int list_get_last(list_t* list, unsigned int* value) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(value == NULL) return 0;

		*value = list_p->arr[list_p->head - 1];

		return 1;
	}

	return 0;
}

int list_contains(list_t* list, unsigned int value) {
	list_pt* list_p = (list_pt*) list;
	int i;

	if(list_p != NULL && list_p->arr != NULL) {
		for(i = 0; i < list_p->size; ++i) {
			if(list_p->arr[i] == value) {
				return 1;
			}
		}
	}

	return 0;
}

int list_remove(list_t* list, size_t index, unsigned int* value) {
	int i;
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(index > list_p->head) return 0;
		if(value != NULL) {
			*value = list_p->arr[index];
		}

		for(i = index + 1; i < list_p->head; ++i) {
			list_p->arr[i-1] = list_p->arr[i];
		}
		--(list_p->head);

		if(list_p->head * 2 >= list_p->size) {
			list_realloc(list_p, list_p->size / 2);
		}

		return 1;
	}

	return 0;
}

int list_remove_last(list_t* list, unsigned int* value) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		if(list_p->head == 0) return 0;
		if(value != NULL) {
			*value = list_p->arr[(list_p->head) - 1];
		}

		--(list_p->head);
		if(list_p->head * 2 >= list_p->size) {
			list_realloc(list_p, list_p->size / 2);
		}

		return 1;
	}

	return 0;
}

int list_length(list_t* list) {
	if(list != NULL) {
		return (int) ((list_pt*)(list))->head;
	}

	return -1;
}

unsigned int* list_as_array(list_t* list) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		unsigned int* ret_array = malloc(list_p->size * sizeof(*ret_array));
		if(ret_array == NULL) {
			return NULL;
		}

		memcpy(ret_array, list_p->arr, list_p->size * sizeof(*ret_array));
		return ret_array;
	}
	return NULL;
}

int list_destroy(list_t* list) {
	list_pt* list_p = (list_pt*) list;

	if(list_p != NULL && list_p->arr != NULL) {
		free(list_p->arr);
		return 1;
	}
	return 0;
}

int list_realloc(list_pt* list, size_t new_size) {
	unsigned int* placeholder_arr;

	if(list != NULL) {
		placeholder_arr = realloc(list->arr, new_size * sizeof(*placeholder_arr));
		if(placeholder_arr == NULL) {
			return 0;
		}
		list->arr = placeholder_arr;
		list->size = new_size;

		return 1;
	}

	return 0;
}