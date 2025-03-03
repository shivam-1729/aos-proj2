#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "gtmpi.h"

int main(int argc, char** argv)
{
  int num_processes, num_rounds = 1000;

  MPI_Init(&argc, &argv);
  double round_latencies[num_rounds];

  if (argc < 2){
    fprintf(stderr, "Usage: ./harness [NUM_PROCS]\n");
    exit(EXIT_FAILURE);
  }

  num_processes = strtol(argv[1], NULL, 10);

  gtmpi_init(num_processes);
  
  double start_time;
  
  for(int k = 0; k < num_rounds; k++){
    start_time = MPI_Wtime() * 1e6;
    gtmpi_barrier();
    round_latencies[k] = MPI_Wtime() * 1e6 - start_time;
  }

  double max_latency;
  double* all_latencies = NULL;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (num_processes > 1) {
      // Only allocate memory for the root process
      if (0 == rank) {
        all_latencies = (double*)malloc(num_processes * num_rounds * sizeof(double));
      }
  }

  // Gather the round latencies from all processes to the root process
  MPI_Gather(round_latencies, num_rounds, MPI_DOUBLE, all_latencies, num_rounds, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double latency_sum = 0.0;
  // Calculate the maximum latency for each round only on the root process
  if (all_latencies != NULL) {
      for (int k = 0; k < num_rounds; k++) {
          max_latency = all_latencies[k];
          for (int i = 1; i < num_processes; i++) {
              if (all_latencies[i * num_rounds + k] > max_latency) {
                  max_latency = all_latencies[i * num_rounds + k];
              }
          }
          latency_sum += max_latency;
          printf("[%d] Max latency for round %d: %.3lf µs\n", rank, k, max_latency);
      }
      printf("Avg latency across all rounds: %.3lf µs\n", latency_sum/ num_rounds);
      free(all_latencies);
  }

  gtmpi_finalize();

  MPI_Finalize();

  return 0;
}
