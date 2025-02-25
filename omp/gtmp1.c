#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include "gtmp.h"

bool DEBUG = false;
#define debug_print(fmt, ...) do { if (DEBUG) printf(fmt, __VA_ARGS__); } while (0) 
// Not sure of the performance hit of these if statements, but it'll definitely be lower than printf

int threads_to_wait_for;
int thread_count;
bool sense = false;
// todo(Gaurav): Sense Reversing Barrier
void gtmp_init(int num_threads){
    // omp_set_num_threads(num_threads);
    thread_count = num_threads;
    threads_to_wait_for = thread_count;

    printf("Init completed\n");
}

void gtmp_barrier(){
    bool my_sense = !sense;

    int thread_id = omp_get_thread_num();
    
    // #pragma omp atomic
    //     threads_to_wait_for--;
    threads_to_wait_for = __sync_fetch_and_sub(&threads_to_wait_for, 1) - 1;
    // __sync_sub_and_fetch() was not atomic

    debug_print("[%d] threads_to_wait_for is now: %d\n", thread_id, threads_to_wait_for);

    if (0 == threads_to_wait_for) {
        debug_print("Thread: %d has now reset the barrier\n", thread_id);
        threads_to_wait_for = thread_count;
        sense = my_sense;
    } else {
        // printf("Thread: %d will now spin\n", thread_id);
        while(my_sense != sense);           // the assumption here is that `sense` and `my_sense` are a cached variables
    }
}

void gtmp_finalize(){
    // No action required to clean up after using OpenMP
    printf("Finalize completed\n");
}

