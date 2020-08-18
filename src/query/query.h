//
//  query.h
//  project
//
//  Created by 郭雅丹 on 2020/8/18.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#ifndef query_h
#define query_h

#include <stdio.h>

struct thread_data{
    int u;
    int v;
    graph_t *g;
    int d;
};

static void* filereadthread(void *arg);
static void* querythread(void *arg);
int query(int u,int v,graph_t*g,int d);






#endif /* query_h */
