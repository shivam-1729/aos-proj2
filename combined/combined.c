#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "gtcombined.h"
#include "../omp/gtmp2.c"
#include "../mpi/gtmpi1.c"

// Todo(Gaurav): Combined barrier with message passing
void gtcombined_init(int num_processes, int num_threads) {
    gtmpi_init(process_cnt);
    gtmp_init(num_threads);
}

void gtcombined_barrier(){
    int thread_id = omp_get_thread_num()

    // 8
    omp_construct_arrival_tree();
    omp_construct_wake_up_tree();
    // 4

    if (0 == thread_id) {
        // 4
        mpi_construct_arrival_tree();
        mpi_construct_wake_up_tree();
        // 1
        mpi_trigger_wake_up();
        // 4
    }

    omp_trigger_wake_up();
    // 8
}

void gtcombined_finalize(){
    gtmpi_finalize();
    gtmp_finalize();
}