#!/bin/bash
#SBATCH --ntasks-per-node=1 
#SBATCH --mem-per-cpu=1G
#SBATCH -t 5
#SBATCH -q coc-ice
#SBATCH -o %x.out
#SBATCH --error %x.err
# Command to run: sbatch --job-name=mpi1_1 --nodes=4 nodes.sbatch ./mpi1 4 
# %x is job name

echo "Started on `/bin/hostname` with $SLURM_NNODES threads & cli param as $2"

module load gcc/12.3.0 mvapich2/2.3.7-1

mpicc -c -g -Wall -std=gnu99 -I. harness.c -o harness.o
mpicc -o mpi1 -g -Wall -std=gnu99 -I.  gtmpi1.c harness.o -lm
mpicc -o mpi2 -g -Wall -std=gnu99 -I.  gtmpi2.c harness.o -lm
mpiexec --ntasks $2 ./mpi1 $2