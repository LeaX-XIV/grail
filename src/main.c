
#include <stdio.h>
#include "list/list.h"
#include "graph/graph.h"
#include "query/query.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct file_data{

    graph_t *g;
    FILE *fp;
};

pthread_mutex_t mutex;

int main(int argc, const char * argv[]) {
    

    int d;
    d=atoi(argv[1]);
    graph_t * g;
    
    g=graph_load(argv[0],d);
    
    //do the labelling
    
    FILE *fp;
    
    pthread_mutex_init(&mutex,NULL);
    
    fp=fopen(argv[2], "r");
    
    void* status;
    int retcode;
    pthread_t th[4];
    struct file_data f;
    
    for(int i=0;i<4;i++){
        
      retcode=pthread_create(&th[i], NULL, filereadthread, &f);
      if (retcode != 0)
          fprintf (stderr, "create GET failed in main %d\n", retcode);
      
    }
    
    for(int j=0;j<4;j++){
        
         pthread_join(th[j],&status);
        
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
