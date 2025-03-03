sbatch --job-name=mpi1_2 --nodes=2 nodes1.sbatch ./mpi1 2
sleep 5s
sbatch --job-name=mpi1_3 --nodes=3 nodes1.sbatch ./mpi1 3
sleep 5s
sbatch --job-name=mpi1_4 --nodes=4 nodes1.sbatch ./mpi1 4
sleep 5s
sbatch --job-name=mpi1_5 --nodes=5 nodes1.sbatch ./mpi1 5
sleep 5s
sbatch --job-name=mpi1_6 --nodes=6 nodes1.sbatch ./mpi1 6
sleep 5s
sbatch --job-name=mpi1_7 --nodes=7 nodes1.sbatch ./mpi1 7
sleep 5s
sbatch --job-name=mpi1_8 --nodes=8 nodes1.sbatch ./mpi1 8
sleep 5s
sbatch --job-name=mpi1_9 --nodes=9 nodes1.sbatch ./mpi1 9
sleep 5s
sbatch --job-name=mpi1_10 --nodes=10 nodes1.sbatch ./mpi1 10
sleep 5s
sbatch --job-name=mpi1_11 --nodes=11 nodes1.sbatch ./mpi1 11
sleep 5s
sbatch --job-name=mpi1_12 --nodes=12 nodes1.sbatch ./mpi1 12

sleep 30s

sbatch --job-name=mpi2_2 --nodes=2 nodes2.sbatch ./mpi2 2
sleep 5s
sbatch --job-name=mpi2_3 --nodes=3 nodes2.sbatch ./mpi2 3
sleep 5s
sbatch --job-name=mpi2_4 --nodes=4 nodes2.sbatch ./mpi2 4
sleep 5s
sbatch --job-name=mpi2_5 --nodes=5 nodes2.sbatch ./mpi2 5
sleep 5s
sbatch --job-name=mpi2_6 --nodes=6 nodes2.sbatch ./mpi2 6
sleep 5s
sbatch --job-name=mpi2_7 --nodes=7 nodes2.sbatch ./mpi2 7
sleep 5s
sbatch --job-name=mpi2_8 --nodes=8 nodes2.sbatch ./mpi2 8
sleep 5s
sbatch --job-name=mpi2_9 --nodes=9 nodes2.sbatch ./mpi2 9
sleep 5s
sbatch --job-name=mpi2_10 --nodes=10 nodes2.sbatch ./mpi2 10
sleep 5s
sbatch --job-name=mpi2_11 --nodes=11 nodes2.sbatch ./mpi2 11
sleep 5s
sbatch --job-name=mpi2_12 --nodes=12 nodes2.sbatch ./mpi2 12