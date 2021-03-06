#include <stdio.h>
#include <pthread.h>

#include "../graph/graph.h"
#include "query.h"

void* filereadthread(void *arg){
    
    int u,v,retVal,res;
    graph_t * g;
    struct alg2 *filedata;
    filedata=(struct alg2 *)arg;
    g=filedata->g;
    pthread_spinlock_t* spin = filedata->spin;
    char* results = filedata->results;
    int* i = filedata->i;
    
    do{
        pthread_spin_lock(spin);
        int index = (*i)++;
        retVal = fscanf (filedata->fp, "%d%d", &u,&v);
        pthread_spin_unlock(spin);
        
        if (retVal!=EOF) {
    
            res=graph_reachable(g, u, v);

            results[index] = (char)res;
        }
    }while(retVal!=EOF);
        
    return arg;
}
