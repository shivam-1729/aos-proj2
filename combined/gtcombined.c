#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>
#include "gtcombined.h"
#include "../omp/gtmp.h"       // todo(Gaurav): check if these will be compiled first
#include "../mpi/gtmpi.h"

// Todo(Gaurav): Combined barrier with message passing
void gtcombined_init(int num_processes, int num_threads) {
    gtmpi_init(num_processes);
    gtmp_init(num_threads);
}

void gtcombined_barrier(){
    // int rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int t_num = omp_get_thread_num();

    gtmp_barrier();
    if(t_num == 0){
        gtmpi_barrier();
    }
    gtmp_barrier();

    // 8
    // printf("omp threads arriving: process - [%d], thread - [%d]\n", rank, t_num);
    // omp_arrival_phase();
    // omp_wake_up_phase();
    // // 4

    // if (0 == t_num) {
    //     // 4
    //     printf("mpi threads arriving: process - [%d]\n", rank);
    //     mpi_arrival_phase();

    //     printf("waking up mpi threads: process - [%d]\n", rank);
    //     mpi_wake_up_phase();
    //     // 1
    //     if (0 == rank){
    //         printf("triggering mpi wakeup: process - [%d]\n", rank);
    //         mpi_trigger_wake_up();
    //     }

    //     printf("triggering omp wakeup: process - [%d], thread - [%d]\n", rank, t_num);
    //     omp_trigger_wake_up();
    //     // 4
    // }
    
    // // 8
    // printf("completed barrier for: process - [%d], thread - [%d]\n", rank, t_num);
}

void gtcombined_finalize(){
    gtmp_finalize();
    gtmpi_finalize();
}