#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "gtmp.h"

int main(int argc, char **argv)
{
  int num_threads, num_rounds = 10;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: ./harness [NUM_THREADS]\n");
    exit(EXIT_FAILURE);
  }
  num_threads = strtol(argv[1], NULL, 10);

  omp_set_dynamic(0);
  if (omp_get_dynamic())
    printf("Warning: dynamic adjustment of threads has been set\n");

  omp_set_num_threads(num_threads);

  gtmp_init(num_threads);

  double all_latencies[num_rounds][num_threads];

#pragma omp parallel shared(num_threads, all_latencies)
  {
    double start_time;
    int thread_id = omp_get_thread_num();

    for (int i = 0; i < num_rounds; i++)
    {
      start_time = omp_get_wtime() * 1e6; // todo(Gaurav): check if walltime should be used
      gtmp_barrier();
      all_latencies[i][thread_id] = omp_get_wtime() * 1e6 - start_time; // Can this array layout cause cache coherence problems?
    }
    // todo(Gaurav): another options is move the OMP parallel block inside the loop. start & end time calculation can be done outside the parallel bock to avoid calculating the max
    // ^ This approach cannot be used for MPI though
  }

  gtmp_finalize();

  double max_latency;
  for (int k = 0; k < num_rounds; k++)
  {
    max_latency = all_latencies[k][0];
    for (int i = 1; i < num_threads; i++)
    {
      if (all_latencies[k][i] > max_latency)
      {
        max_latency = all_latencies[k][i];
      }
    }
    printf("Max latency for round %d: %.3lf µs\n", k, max_latency); // todo(Gaurav): can also do max_end_time - min_end_time
  }

  return 0;
}
