
#include "query.h"
#include <stdio.h>
#include "../list/list.h"
#include "../graph/graph.h"
#include "../interval/interval.h"
#include <pthread.h>


int query(int u,int v,graph_t*g){
    for(int i=0;i<g->d;i++){
        if(interval_check(g->g[u].labels[i],g->g[v].labels[i]) == 0){
            return 0; // 0
        }
        
    }
    
    if(list_contains(g->g[u].rowAdj, g->g[v].id)||g->g[u].id==g->g[v].id){
        return 1; // 1
    }
    
    int s=list_length(g->g[u].rowAdj);

    for(int j=0;j<s;j++){
        unsigned int c;
        list_get(g->g[u].rowAdj, j, &c);
        if(query(c, v, g) == 1) {
            return 1;
        } 
    }

    return 0;
}



// int querythread(void *arg){
    
//     int u;
//     int v;
//     graph_t * g;
    
//     int res;
//     int flag=0;
    
//     struct thread_data *mydata;
//     mydata=(struct thread_data *)arg;
    
//     u=mydata->u;
//     v=mydata->v;
//     g=mydata->g;
    
//     for(int i=0;i<g->d;i++){
//         if(interval_check(g->g[u].labels[i],g->g[v].labels[i])!=1){
//             return 0; // 0
//         }
        
//     }
    
//     if(list_contains(g->g[u].rowAdj, g->g[v].id)||g->g[u].id==g->g[v].id){
//         return 1; // 1
//     }
    
    
//     int s=list_length(g->g[u].rowAdj);
    
//     // pthread_t *th=(pthread_t *)malloc(sizeof(pthread_t)*s);
//     // void* status;
//     // int retcode;
    
//     for(unsigned int j=0;j<s;j++){
        
//         struct thread_data uv;
//         list_get(g->g[u].rowAdj, &j, &uv.u);
//         uv.v=v;
//         uv.g=g;
        
//         // retcode=pthread_create(&th[j], NULL, querythread, &uv);
//         // if (retcode != 0)
//         //     fprintf (stderr, "create GET failed in querythread %d\n", retcode);
//         if(querythread(&uv) == 1) {
//             return 1;
//         } 
//     }

//     return 0;
//     // for(int j=0;j<s;j++){
        
//     //     //  pthread_join(th[j],&status);
//     //      res=*((int*)status);
//     //      if(res==1)
//     //          flag=1;
        
//     // }

//     // if(flag==1)
//     //     pthread_exit((void *) 1);
//     // else
//     //     pthread_exit((void *) 0);
    
// }


void* filereadthread(void *arg){
    
    int u,v,retVal,res;
    graph_t * g;
    struct file_data *filedata;
    filedata=(struct file_data *)arg;
    g=filedata->g;
    pthread_mutex_t* mutex = filedata->mutex;
    
    do{
    
        pthread_mutex_lock(mutex);
        retVal = fscanf (filedata->fp, "%d%d", &u,&v);
        pthread_mutex_unlock(mutex);
        
        if (retVal!=EOF) {
    
            res=query(u,v,g);
            pthread_mutex_lock(mutex);
            if(res==1)
                fprintf (stdout, "query: %d and %d is reachable\n",u, v);
            else
                fprintf (stdout, "query: %d and %d is not reachable\n",u, v);
            pthread_mutex_unlock(mutex);
        }
    }while(retVal!=EOF);
        
    return arg;
}
