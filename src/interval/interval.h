#ifndef INTERVAL_HEADER
#define INTERVAL_HEADER

struct interval{
	int first;
	int second;
};

typedef struct interval interval_t;

interval_t* interval_create(int first, int second);
int interval_first(interval_t*);
int interval_second(interval_t*);
int interval_check(interval_t* i1, interval_t* i2);
void interval_destroy(interval_t* i);

#endif // INTERVAL_HEADER