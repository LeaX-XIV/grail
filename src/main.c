
#include <stdio.h>
#include "list/list.h"
#include "graph/graph.h"
#include "query/query.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysinfo.h>

pthread_mutex_t mutex;

int main(int argc, char * argv[]) {
    
    srand(time(0));

    int nproc = get_nprocs_conf();
    // int nproc = 4;
    printf("%d\n", nproc);

    int d;
    d=atoi(argv[2]);
    graph_t * g;
    
    void* status;
    int retcode;
    pthread_t th[4];
    struct file_data f;
    
    FILE *fp;
    
    g=graph_load(argv[1],d);    
        
    pthread_mutex_init(&mutex,NULL);
    
    fp=fopen(argv[3], "r");
    
    f.g = g;
    f.fp = fp;
    f.mutex = &mutex;
    for(int i=0;i<nproc;i++){
      retcode=pthread_create(&th[i], NULL, filereadthread, &f);
      if (retcode != 0)
          fprintf (stderr, "create GET failed in main %d\n", retcode);
    }
    
    for(int j=0;j<nproc;j++){
         pthread_join(th[j],&status);
    }

    printf("query finish..\n");
    pthread_mutex_destroy(&mutex);
    fclose(fp);
    return 0;
}

