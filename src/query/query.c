
#include "query.h"
#include <stdio.h>
#include "..list/list.h"
#include "..graph/graph.h"
#include "..interval/interval.h"
#include <pthread.h>


int query(int u,int v,graph_t*g,int d){
         

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
    
    int res=(int*)status;
    
    if(status==1)
        return 1;
    else
        return 0;
     
}



static void* querythread(void *arg){
    
    int u;
    int v;
    graph_t * g;
    int d;
    
    int res;
    int flag=0;
    
    struct thread_data *mydata;
    mydata=(struct thread_data *)arg;
    
    u=mydata->u;
    v=mydata->v;
    g=mydata->g;
    d=mydata->d;
    
    for(int i=0;i<d;i++){
        if(interval_check(g->g[u].labels[i],g->g[v].labels[i])!=1){
            pthread_exit((void *) 0);
        }
        
    }
    
    if(g->g[u].rowAdj.contains(g->g[v].id)||g->g[u].id==g->g[v].id){
        pthread_exit((void *) 1);
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
            fprintf (stderr, "create GET failed in querythread %d\n", retcode);
    }
    
    for(int j=0;j<s;j++){
        
         pthread_join(th[j],&status);
         res=(int*)status;
         if(res==1)
             flag=1;
        
    }

    if(flag==1)
        pthread_exit((void *) 1);
    else
        pthread_exit((void *) 0);
}


static void* filereadthread(void *arg){
    
    int u,v,retVal,res;
    graph_t * g;
    struct file_data *filedata;
    filedata=(struct file_data *)arg;
    
    g=filedata->g;
    
    do{
    
        pthread_mutex_lock(&mutex);
        retVal = fscanf (filedata->fp, "%d%d", &u,&v);
        pthread_mutex_unlock(&mutex);
        
        if (retVal!=EOF) {
    
            res=query(u,v,g,g->nv);
            if(res==1)
                fprintf (stdout, "query: %d and %d is reachable\n",u, v);
            else
                fprintf (stdout, "query: %d and %d is not reachable\n",u, v);
        }
    }while(retVal!=EOF)
        
    pthread_exit(NULL);
}
