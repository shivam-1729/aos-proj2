#!/bin/bash
#SBATCH --nodes 1
#SBATCH --mem-per-cpu=1G
#SBATCH -t 5
#SBATCH -q coc-ice
#SBATCH -o %x.out           
#SBATCH --error %x.err

# Command to run: sbatch --job-name=mp2_1 --cpus-per-task=4 threads.sbatch ./mp2 4 
# %x is job name

echo "Started on `/bin/hostname` with $SLURM_CPUS_PER_TASK threads & cli param as $2"

module load gcc/12.3.0 mvapich2/2.3.7-1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

make
./mp2 $2