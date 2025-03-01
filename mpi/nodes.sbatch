#!/bin/bash

#SBATCH -J cs6210-proj2-mpi1
#SBATCH --ntasks-per-node=1 --nodes 8 
#SBATCH --mem-per-cpu=1G
#SBATCH -t 5
#SBATCH -q coc-ice
#SBATCH -o mpi1.out

echo "Started on `/bin/hostname`"

module load gcc/12.3.0 mvapich2/2.3.7-1
mpicc -Wall mpi_hello.c -o mpi_hello

srun ./mpi1

# This file is WIP