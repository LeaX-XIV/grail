#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#include "list/list.h"
#include "graph/graph.h"
#include "query/query.h"


int main(int argc, char * argv[]) {

    if(argc < 4) {
        fprintf(stdout, "Expeted arguments in the from of:\n\tgrail <graph_file> <d> <query_file>");
        return EXIT_SUCCESS;
    }
    
    srand(time(0));

    int nproc = get_nprocs_conf();
    // int nproc = 4;

    int d=atoi(argv[2]);
    
    int retcode;
    pthread_t* th = malloc(nproc * sizeof(*th));
    struct file_data f;
    
    graph_t * g=graph_load(argv[1],d);
    FILE *fp=fopen(argv[3], "r");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);

    if(g == NULL || fp == NULL) {
        fprontf(stdout, "Error\n");
        return EXIT_FAILURE;
    }

    f.g = g;
    f.fp = fp;
    f.mutex = &mutex;

    for(int i=0;i<nproc;i++){
      retcode=pthread_create(&th[i], NULL, filereadthread, &f);
      if (retcode != 0)
          fprintf (stderr, "create GET failed in main %d\n", retcode);
    }
    
    for(int j=0;j<nproc;j++){
         pthread_join(th[j],NULL);
    }

    printf("query finish..\n");
    pthread_mutex_destroy(&mutex);
    fclose(fp);
    free(th);
    return EXIT_SUCCESS;
}

