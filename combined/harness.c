#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
// #include "../omp/gtmp2.c"
// #include "../mpi/gtmpi1.c"
#include "gtcombined.h"

int main(int argc, char **argv)
{
  int num_processes, num_threads, num_rounds = 1;

  MPI_Init(&argc, &argv);
  double round_latencies[num_rounds];

  if (argc < 2)
  {
    fprintf(stderr, "Usage: ./harness [NUM_THREADS]\n");
    exit(EXIT_FAILURE);
  }

  MPI_Comm_size(MPI_COMM_WORLD, &num_processes); 
  num_threads = strtol(argv[1], NULL, 10);

  omp_set_dynamic(0);
  if (omp_get_dynamic())
    printf("Warning: dynamic adjustment of threads has been set\n");

  omp_set_num_threads(num_threads);

  gtcombined_init(num_processes, num_threads);
  //gtmpi_init(num_processes);
  //gtmp_init(num_threads);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double start_time;

  #pragma omp parallel shared(num_threads)
  {
    for (int k = 0; k < num_rounds; k++)
    {
      start_time = MPI_Wtime() * 1e6;
      int t_num = omp_get_thread_num();
      printf("round [%d]: process - [%d] thread - [%d]\n", k, rank, t_num);
      // if (t_num == 0)
      // {
      //     gtmpi_barrier();
      //     gtmp_barrier();

      //     printf("round [%d]: process - [%d] thread - [%d] completed barrier\n", k, rank, t_num);
      // }
      // else
      // {
      //     gtmp_barrier();
      //     printf("round [%d]: process - [%d] thread - [%d] completed barrier\n", k, rank, t_num);
      // }
      gtcombined_barrier();
      round_latencies[k] = MPI_Wtime() * 1e6 - start_time;
      printf("round [%d]: process - [%d] thread - [%d] completed barrier\n", k, rank, t_num);
    }
  }

  // todo(Gaurav): latency calculation
  double max_latency;
  double *all_latencies = NULL;

  if (num_processes > 1)
  {
    // Only allocate memory for the root process
    if (0 == rank)
    {
      all_latencies = (double *)malloc(num_processes * sizeof(double));
    }
  }

  // Gather the round latencies from all processes to the root process
  MPI_Gather(round_latencies, num_rounds, MPI_DOUBLE, all_latencies, num_rounds, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // Calculate the maximum latency for each round only on the root process
  if (all_latencies != NULL)
  {
    for (int k = 0; k < num_rounds; k++)
    {
      max_latency = all_latencies[k];
      for (int i = 1; i < num_processes; i++)
      {
        if (all_latencies[i * num_rounds + k] > max_latency)
        {
          max_latency = all_latencies[i * num_rounds + k];
        }
      }
      printf("[%d] Max latency for round %d: %.3lf µs\n", rank, k, max_latency);
    }
    free(all_latencies);
  }

  gtcombined_finalize();
  //gtmp_finalize();
  //gtmpi_finalize();

  MPI_Finalize();

  return 0;
}
