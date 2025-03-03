#include <omp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gtmp.h"

typedef struct {
	bool parentsense;
	bool* parentpointer;
	bool* childpointers[2];
	
    bool havechild[4];
    bool childnotready[4];

    bool dummy;
	bool sense;
}Node;

static Node* threads;

void gtmp_init(int num_threads){
    threads = (Node* )malloc(sizeof(Node) * num_threads);
    memset(threads, 0, sizeof(Node) * num_threads);

    printf("Init completed\n");

    for (int i=0; i<num_threads; i++) 
    {
		//arrival tree
        for(int j=0; j<4; j++) 
        {
			if(4*i + j + 1 < num_threads) 
            {
				threads[i].havechild[j] = true;
			}
			else 
            {
				threads[i].havechild[j] = false;
			}
            threads[i].childnotready[j] = threads[i].havechild[j];
		}
        
        if (i==0) 
        {
			threads[i].parentpointer = (bool* )&(threads[i].dummy);
		}
		else
        {
			threads[i].parentpointer = &(threads[(i-1)/4].childnotready[(i-1)%4]);
		}

		//wakeup tree
		for(int j=0; j<2; j++) 
        {
			if (2*i + j + 1 < num_threads)
            {
                threads[i].childpointers[j] = &(threads[i*2+j+1].parentsense);
            }
				
			else
            {
                threads[i].childpointers[j] = &(threads[i].dummy);
            }
		}

		threads[i].parentsense = false;
		threads[i].sense = true;
	}
}

void omp_construct_arrival_tree(){

}
void omp_contruct_wake_up_tree(){

}
void omp_trigger_wake_up(){
    
}

void gtmp_barrier(){
    int t_num = omp_get_thread_num();
	printf("thread %d entered barrier\n", t_num);
    fflush(stdout);

    for (int j = 0; j < 4; j++)
    {
        while (threads[t_num].childnotready[j]) {}
    }

	for (int j = 0; j < 4; j++)
    {
        threads[t_num].childnotready[j] = threads[t_num].havechild[j];
    }
    
    *threads[t_num].parentpointer = false;
	
    if (t_num != 0)
    {
        while(threads[t_num].parentsense != threads[t_num].sense);
    }
		
	*threads[t_num].childpointers[0] = threads[t_num].sense;
	*threads[t_num].childpointers[1] = threads[t_num].sense;

	threads[t_num].sense = !threads[t_num].sense;
    printf("thread %d exited barrier\n", t_num);
    fflush(stdout);
}

void gtmp_finalize(){
    free(threads);
    threads = NULL;
    printf("Finalize completed\n");
}