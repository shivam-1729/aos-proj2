#!/bin/bash
#SBATCH --ntasks-per-node=1 
#SBATCH --mem-per-cpu=1G
#SBATCH -t 5
#SBATCH -q coc-ice
#SBATCH -o %x.out
#SBATCH --error %x.err
# Command to run: sbatch --job-name=combined_1 --nodes=4 --cpus-per-task=4 combined.sbatch ./combined 4 
# %x is job name

echo "Started on `/bin/hostname` with $SLURM_NNODES nodes, $SLURM_CPUS_PER_TASK cpus-per-task & cli param as $2"

module load gcc/12.3.0 mvapich2/2.3.7-1

mpicc.mpich -o combined -g -Wall -fopenmp -std=gnu99 -I. gtcombined.c harness.o -lgomp -lm
# mpiexec --ntasks $2 ./mpi1 $2         # Not sure if this will assign a process to each node
srun --nodes $SLURM_NNODES --cpus-per-task $SLURM_CPUS_PER_TASK ./combined $2