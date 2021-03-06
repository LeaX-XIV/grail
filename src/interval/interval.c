#include <stdio.h>
#include <stdlib.h>

#include "interval.h"

interval_t* interval_create(int first, int second){
    interval_t* i;
    
    i = calloc (1, sizeof(*i));
    
    i->first=first;
    i->second=second;
    return i;
    
}

int interval_first(interval_t* i){
    
    int f;
    f=i->first;
    return f;
    
}
int interval_second(interval_t* i){
    
    int s;
    s=i->second;
    return s;
}

int interval_check(interval_t* i1, interval_t* i2){
    if(i1 == NULL || i2 == NULL)
        return 0;
    int f1,f2,s1,s2;
    f1=i1->first;
    f2=i2->first;
    s1=i1->second;
    s2=i2->second;
    
    if(f2>=f1&&s2<=s1)
        return 1;
    else
        return 0;
    
}

void interval_destroy(interval_t* i){
    if(i == NULL)
        return;
    free(i);
    
}
