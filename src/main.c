#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "list/list.h"
#include "graph/graph.h"
#include "query/query.h"



int main(int argc, char * argv[]) {

	if(argc < 4) {
		fprintf(stdout, "Expeted arguments in the from of:\n\tgrail <graph_file> <d> <query_file>\n");
		return EXIT_SUCCESS;
	}
	
	srand(time(NULL));


	int nproc = get_nprocs_conf();
	// int nproc = 4;

	int d=atoi(argv[2]);
	int n_lines = 0;
	int index = 0;
	int i, u, v;
	char* results;
	
	int retcode;
	pthread_t* th = malloc(nproc * sizeof(*th));
	struct alg2 f;
	
	struct timeval s1,s2,s3,s4;
	gettimeofday( &s1, NULL );
		
	graph_t * g=graph_load(argv[1],d);
	
	gettimeofday( &s2, NULL );
	int timeuse1 = 1000000 * ( s2.tv_sec - s1.tv_sec ) + s2.tv_usec - s1.tv_usec;
		
	FILE *fp=fopen(argv[3], "r");
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);
	
	if(g == NULL || fp == NULL) {
		fprintf(stderr, "Error\n");
		return EXIT_FAILURE;
	}

	while((i = fscanf(fp, "%d %d", &u, &v)) != EOF) {
		++n_lines;
	}
	results = calloc(n_lines, sizeof(*results));

	if(results == NULL) {
		fprintf(stderr, "Error\n");
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_SET);

	f.g = g;
	f.fp = fp;
	f.mutex = &mutex;
	f.results = results;
	f.i = &index;
	
	gettimeofday( &s3, NULL );
	
	for(i=0;i<nproc;i++){
		retcode=pthread_create(&th[i], NULL, filereadthread, &f);
		if (retcode != 0) {
			fprintf (stderr, "Cannot create thread. Aborting...\n");
		
			for(int j = 0; j < i; ++j) {
				pthread_cancel(th[j]);
			}

			free(results);
			pthread_mutex_destroy(&mutex);
			graph_dispose(g);
			fclose(fp);
			free(th);
			return EXIT_FAILURE;
		}
	}
	
	for(i=0; i < nproc; i++){
		 pthread_join(th[i],NULL);
	}
	
	fseek(fp, 0, SEEK_SET);
	
	for(i = 0; i < n_lines; ++i) {
		fscanf (fp, "%d%d", &u,&v);
		if(f.results[i]==1)
			fprintf (stdout, "query: %d is reachable from %d\n", v, u);
		else
			fprintf (stdout, "query: %d is not reachable from %d\n", v, u);
	}

	gettimeofday( &s4, NULL );
	int timeuse2 = 1000000 * ( s4.tv_sec - s3.tv_sec ) + s4.tv_usec - s3.tv_usec;
	
	printf("query finish..\n");
	
	printf("Time to create the index: %d us\n", timeuse1);
	printf("Size of the index: %ld bytes\n", graph_size(g));
	printf("Time to execute %d queries: %d us, with an average of %.2f us per query\n", n_lines, timeuse2, ((float)timeuse2 / n_lines));
	
	free(results);
	pthread_mutex_destroy(&mutex);
	graph_dispose(g);
	fclose(fp);
	free(th);
	return EXIT_SUCCESS;
}

