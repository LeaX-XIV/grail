#include <stdlib.h>
#include "list.h"

int list_realloc(list_t* list, size_t new_size);

int list_init(list_t* list, size_t initial_size) {
	unsigned int placeholder_arr;
	
	if(list != NULL) {
		placeholder_arr = malloc(initial_size * (sizeof list->arr));
		if(placeholder_arr == NULL) {
			list->arr = NULL;
			list->size = 0;
			list->head = 0;
			return 0;
		}
		list->arr = placeholder_arr;
		list->size = initial_size;
		list->head = 0;

		return 1;
	}

	return 0;
}

int list_append(list_t* list, unsigned int value) {
	if(list != NULL && list->arr != NULL) {
		if(list->size == list->head) { // Array is full, need reallocation O(n)
			if(list_realloc(list, list->size * 2) == 0) {
				return 0;
			}
		}

		list->arr[list->head] = value;
		(list->head)++;
		return 1;
	}

	return 0;
}

int list_insert(list_t* list, unsigned int value, size_t pos) {
	int i;

	if(list != NULL && list->arr != NULL) {
		if(pos > list->head) return 0;

		if(list->size == list->head) { // Array is full, need reallocation O(n)
			if(list_realloc(list, list->size * 2) == 0) {
				return 0;
			}
		}

		for(i = list->head; i > pos; --i) {
			list->arr[i] = list->arr[i-1];
		}
		list->arr[pos] = value;
		++(list->head);

		return 1;
	}

	return 0;
}

int list_get(list_t* list, size_t index, unsigned int* value) {
	if(list != NULL && list->arr != NULL) {
		if(value == NULL) return 0;
		if(index > list->head) return 0;

		*value = list->arr[index];

		return 1;
	}

	return 0;
}

int list_get_last(list_t* list, unsigned int value) {
	if(list != NULL && list->arr != NULL) {
		if(value == NULL) return 0;

		*value = list->arr[list->head - 1];

		return 1;
	}

	return 0;
}

int list_remove(list_t* list, size_t index, unsigned int* value) {
	int i;

	if(list != NULL && list->arr != NULL) {
		if(index > list->head) return 0;
		if(value != NULL) {
			*value = list->arr[index];
		}

		for(i = index + 1; i < list->head; ++i) {
			list->arr[i-1] = list->arr[i];
		}
		--(list->head);

		if(list->head * 2 >= list->size) {
			list_realloc(list, list->size / 2);
		}

		return 1;
	}

	return 0;
}

int list_remove_last(list_t* list, unsigned int* value) {
	int i;

	if(list != NULL && list->arr != NULL) {
		if(list->head == 0) return 0;
		if(value != NULL) {
			*value = list->arr[(list->head) - 1];
		}

		--(list->head);
		if(list->head * 2 >= list->size) {
			list_realloc(list, list->size / 2);
		}

		return 1;
	}

	return 0;
}

int list_length(list_t* list) {
	if(list != NULL) {
		return (int) list->head;
	}

	return -1;
}

int list_destroy(list_t* list) {
	if(list != NULL && list->arr != NULL) {
		free(list->arr);
		return 1;
	}
	return 0;
}

int list_realloc(list_t* list, size_t new_size) {
	unsigned int placeholder_arr;

	if(list != NULL) {
		placeholder_arr = realloc(list->arr, new_size);
		if(placeholder_arr == NULL) {
			return 0;
		}
		list->arr = placeholder_arr;
		list->size = new_size;

		return 1;
	}

	return 0;
}