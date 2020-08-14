//
//  main.c
//  project
//
//  Created by 郭雅丹 on 2020/8/13.
//  Copyright © 2020 GUO YADAN. All rights reserved.
//

#include <stdio.h>
#include "list/list.h"
#include "graph/graph.h"
#include <pthread.h>



struct thread_data{
    int u;
    int v;
    graph_t *g;
    int d;
};

int flag=0;
static void* querythread(void *arg);


int query(int u,int v,graph_t*g,int d){
         
    int f1,f2,s1,s2;
        
    for(int i=0;i<d;i++){
            
        f1=g->g[u].labels[i].first;
        f2=g->g[v].labels[i].first;
        s1=g->g[u].labels[i].second;
        s2=g->g[v].labels[i].second;
            
        if(f1>f2||s1<s2){
            return 0;
        }
    }
    
    flag=0;
    
    void* status;
    pthread_t th;
    int retcode;
    struct thread_data uv;
    uv.u=u;
    uv.v=v;
    uv.g=g;
    uv.d=d;
    
    retcode=pthread_create(&th, NULL, querythread, &uv);
    if (retcode != 0)
        fprintf (stderr, "create GET failed %d\n", retcode);
    
    pthread_join(th,&status);
    
    if(flag>0)
        return 1;
    else
        return 0;
     
}



static void* querythread(void *arg){
    
    int u;
    int v;
    graph_t * g;
    int d;
    
    struct thread_data *mydata;
    mydata=(struct thread_data *)arg;
    u=mydata->u;
    v=mydata->v;
    g=mydata->g;
    d=mydata->d;
    
    
    int f1,f2,s1,s2;
    
    for(int i=0;i<d;i++){
        
        f1=g->g[u].labels[i].first;
        f2=g->g[v].labels[i].first;
        s1=g->g[u].labels[i].second;
        s2=g->g[v].labels[i].second;
        
        if(f1>f2||s1<s2){
            flag+=0;
            return 0;
        }
        
    }
    
    if(g->g[u].rowAdj.contains(g->g[v].id)||g->g[u].id==g->g[v].id){
        flag++;
        return 0;
    }
    
    
    int s=sizeof(g->g[u].rowAdj);
    
    pthread_t *th=(pthread_t *)malloc(sizeof(pthread_t)*s);
    
    void* status;
    int retcode;
    
    for(int j=0;j<s;j++){
        
        struct thread_data uv;
        uv.u=g->g[u].rowAdj[j];
        uv.v=v;
        uv.g=g;
        uv.d=d;
        
        retcode=pthread_create(&th[j], NULL, querythread, &uv);
        if (retcode != 0)
            fprintf (stderr, "create GET failed %d\n", retcode);
        
    }
    
    for(int j=0;j<s;j++){
        
         pthread_join(th[j],&status);
        
    }

    
}
