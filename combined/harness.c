#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
// #include "../omp/gtmp2.c"
// #include "../mpi/gtmpi1.c"
#include "gtcombined.h"

int main(int argc, char **argv)
{
  int num_processes, num_threads, num_rounds = 1000;

  MPI_Init(&argc, &argv);

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
  double round_thread_latencies[num_rounds][num_threads];
  double round_node_latencies[num_rounds];
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
      round_thread_latencies[k][t_num] = MPI_Wtime() * 1e6 - start_time;
      printf("round [%d]: process - [%d] thread - [%d] completed barrier\n", k, rank, t_num);
    }
  }

  // Calculating max latency among threads on a node per round
  double latency_sum = 0.0;
  double max_latency;
  for (int k = 0; k < num_rounds; k++)
  {
    max_latency = round_thread_latencies[k][0];
    for (int i = 1; i < num_threads; i++)
    {
      if (round_thread_latencies[k][i] > max_latency)
      {
        max_latency = round_thread_latencies[k][i];
      }
    }
    round_node_latencies[k] = max_latency;
    // printf("[%d] Thread max latency for round %d: %.3lf µs\n", rank, k, max_latency); // todo(Gaurav): can also do max_end_time - min_start_time
  }

  // Calculating avg latency of threads on a node per round
  // Gather the round latencies from all processes to the root process
  MPI_Gather(round_node_latencies, num_rounds, MPI_DOUBLE, NULL, 0, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // Calculate the maximum latency for each round only on the root process
  if (0 == rank)
  {
    double all_latencies[num_processes][num_rounds];
    MPI_Gather(round_node_latencies, num_rounds, MPI_DOUBLE, all_latencies, num_rounds, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int k = 0; k < num_rounds; k++)
    {
      max_latency = all_latencies[0][k];
      for (int i = 1; i < num_processes; i++)
      {
        if (all_latencies[i][k] > max_latency)
        {
          max_latency = all_latencies[i][k];
        }
      }
      latency_sum += max_latency;
      printf("[%d] Max latency for round %d: %.3lf µs\n", rank, k, max_latency);
    }
    printf("Avg latency across all rounds: %.3lf µs\n", latency_sum/ num_rounds);
  }

  gtcombined_finalize();
  //gtmp_finalize();
  //gtmpi_finalize();

  MPI_Finalize();

  return 0;
}
