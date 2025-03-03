#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include "gtmpi.h"

static int P, num_rounds;
void gtmpi_init(int num_processes){
    P = num_processes;
    num_rounds = ceil(log2(num_processes*1.0));
}

void gtmpi_barrier(){
    int my_id, my_dst, my_src;
    int tag = 1;
    MPI_Status mpi_result;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    for (int i = 0; i < num_rounds; i++)
    {
        my_dst = (my_id + (1<<i)) % P;
        my_src = (my_id - (1<<i) + P) % P;

        MPI_Send(NULL, 0, MPI_INT, my_dst, tag, MPI_COMM_WORLD);
        MPI_Recv(NULL, 0, MPI_INT, my_src, tag, MPI_COMM_WORLD, &mpi_result);

        printf("proc %d: received message from proc %d of %d\n", my_id, my_src, P);
        fflush(stdout);
        
    }
}

void gtmpi_finalize(){

}