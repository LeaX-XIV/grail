
#include <stdio.h>
#include <pthread.h>

#include "../graph/graph.h"
#include "query.h"

void* filereadthread(void *arg){
    
    int u,v,retVal,res;
    graph_t * g;
    struct file_data *filedata;
    filedata=(struct file_data *)arg;
    g=filedata->g;
    pthread_mutex_t* mutex = filedata->mutex;
    int* results = filedata->results;
    int* i = filedata->i;
    
    do{
        pthread_mutex_lock(mutex);
        int index = (*i)++;
        retVal = fscanf (filedata->fp, "%d%d", &u,&v);
        pthread_mutex_unlock(mutex);
        
        if (retVal!=EOF) {
    
            res=graph_reachable(g, u, v);

            results[index] = res;

            // pthread_mutex_lock(mutex);
            // if(res==1)
            //     fprintf (stdout, "query: %d and %d is reachable\n",u, v);
            // else
            //     fprintf (stdout, "query: %d and %d is not reachable\n",u, v);
            // pthread_mutex_unlock(mutex);
        }
    }while(retVal!=EOF);
        
    return arg;
}
