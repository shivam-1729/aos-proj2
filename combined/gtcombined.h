#ifndef GTCOM_H
#define GTCOM_H

void gtcombined_init(int num_processes, int num_threads);
void gtcombined_barrier();
void gtcombined_finalize();

#endif
