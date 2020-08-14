//
//  interval.c
//  project
//
//  Created by 郭雅丹 on 2020/8/14.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#include "interval.h"
#include "stdlib.h"
#include <stdio.h>

interval_t* interval_create(int first, int second){
    interval_t* i;
    
    i = (interval_t*) calloc (1, sizeof(interval_t));
    
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
    
    free(i);
    
}



