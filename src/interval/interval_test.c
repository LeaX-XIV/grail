#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "interval.h"

int main() {

	interval_t* t1 = interval_create(1, 10);
	interval_t* t2 = interval_create(-3, -1);
	interval_t* t3 = interval_create(1, 1);
	interval_t* t4 = interval_create(5, 5);
	interval_t* t5 = interval_create(10, 10);
	interval_t* t6 = interval_create(15, 19);
	interval_t* t7 = interval_create(-1, 6);
	interval_t* t8 = interval_create(5, 16);
	interval_t* t9 = interval_create(-5, 15);	
	
	assert(interval_check(t1, t2) == 0);
	assert(interval_check(t1, t3) == 1);
	assert(interval_check(t1, t4) == 1);
	assert(interval_check(t1, t5) == 1);
	assert(interval_check(t1, t6) == 0);
	assert(interval_check(t1, t7) == 0);
	assert(interval_check(t1, t8) == 0);
	assert(interval_check(t1, t9) == 0);

	interval_destroy(t1);
	interval_destroy(t2);
	interval_destroy(t3);
	interval_destroy(t4);
	interval_destroy(t5);
	interval_destroy(t6);
	interval_destroy(t7);
	interval_destroy(t8);
	interval_destroy(t9);

	return 1;
}