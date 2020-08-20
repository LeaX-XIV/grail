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
    int n_lines = 0;
    int index = 0;
    int i, u, v;
    int* results;
    
    int retcode;
    pthread_t* th = malloc(nproc * sizeof(*th));
    struct file_data f;
    
    graph_t * g=graph_load(argv[1],d);
    
    FILE *fp=fopen(argv[3], "r");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    
    if(g == NULL || fp == NULL) {
        fprintf(stdout, "Error\n");
        return EXIT_FAILURE;
    }

    while((i = fscanf(fp, "%d %d", &u, &v)) != EOF) {
        ++n_lines;
    }
    results = calloc(n_lines, sizeof(*results));

    if(results == NULL) {
        fprintf(stdout, "Error\n");
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_SET);

    f.g = g;
    f.fp = fp;
    f.mutex = &mutex;
    f.results = results;
    f.i = &index;

    for(i=0;i<nproc;i++){
      retcode=pthread_create(&th[i], NULL, filereadthread, &f);
      if (retcode != 0)
          fprintf (stderr, "create GET failed in main %d\n", retcode);
    }
    
    for(int j=0;j<nproc;j++){
         pthread_join(th[j],NULL);
    }
    
    fseek(fp, 0, SEEK_SET);

    for(i = 0; i < n_lines; ++i) {
        fscanf (fp, "%d%d", &u,&v);
        if(f.results[i]==1)
            fprintf (stdout, "query: %d and %d is reachable\n",u, v);
        else
            fprintf (stdout, "query: %d and %d is not reachable\n",u, v);
    }

    printf("query finish..\n");
    free(results);
    pthread_mutex_destroy(&mutex);
    graph_dispose(g);
    fclose(fp);
    free(th);
    return EXIT_SUCCESS;
}

