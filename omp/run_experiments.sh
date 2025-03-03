sbatch --job-name=mp1_2 --cpus-per-task=2 threads1.sbatch ./mp1 2
sleep 5s
sbatch --job-name=mp1_3 --cpus-per-task=3 threads1.sbatch ./mp1 3
sleep 5s
sbatch --job-name=mp1_4 --cpus-per-task=4 threads1.sbatch ./mp1 4
sleep 5s
sbatch --job-name=mp1_5 --cpus-per-task=5 threads1.sbatch ./mp1 5
sleep 5s
sbatch --job-name=mp1_6 --cpus-per-task=6 threads1.sbatch ./mp1 6
sleep 5s
sbatch --job-name=mp1_7 --cpus-per-task=7 threads1.sbatch ./mp1 7
sleep 5s
sbatch --job-name=mp1_8 --cpus-per-task=8 threads1.sbatch ./mp1 8

sleep 30s

sbatch --job-name=mp2_2 --cpus-per-task=2 threads2.sbatch ./mp2 2
sleep 5s
sbatch --job-name=mp2_3 --cpus-per-task=3 threads2.sbatch ./mp2 3
sleep 5s
sbatch --job-name=mp2_4 --cpus-per-task=4 threads2.sbatch ./mp2 4
sleep 5s
sbatch --job-name=mp2_5 --cpus-per-task=5 threads2.sbatch ./mp2 5
sleep 5s
sbatch --job-name=mp2_6 --cpus-per-task=6 threads2.sbatch ./mp2 6
sleep 5s
sbatch --job-name=mp2_7 --cpus-per-task=7 threads2.sbatch ./mp2 7
sleep 5s
sbatch --job-name=mp2_8 --cpus-per-task=8 threads2.sbatch ./mp2 8