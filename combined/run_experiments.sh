sbatch --job-name=combined_2n_2t --nodes=2 --cpus-per-task=2 combined.sbatch ./combined 2
sbatch --job-name=combined_2n_4t --nodes=2 --cpus-per-task=4 combined.sbatch ./combined 4
sbatch --job-name=combined_2n_6t --nodes=2 --cpus-per-task=6 combined.sbatch ./combined 6
sbatch --job-name=combined_2n_8t --nodes=2 --cpus-per-task=8 combined.sbatch ./combined 8
sbatch --job-name=combined_2n_10t --nodes=2 --cpus-per-task=10 combined.sbatch ./combined 10
sbatch --job-name=combined_2n_12t --nodes=2 --cpus-per-task=12 combined.sbatch ./combined 12

sleep 30s

sbatch --job-name=combined_4n_2t --nodes=4 --cpus-per-task=2 combined.sbatch ./combined 2
sbatch --job-name=combined_4n_4t --nodes=4 --cpus-per-task=4 combined.sbatch ./combined 4
sbatch --job-name=combined_4n_6t --nodes=4 --cpus-per-task=6 combined.sbatch ./combined 6
sbatch --job-name=combined_4n_8t --nodes=4 --cpus-per-task=8 combined.sbatch ./combined 8
sbatch --job-name=combined_4n_10t --nodes=4 --cpus-per-task=10 combined.sbatch ./combined 10
sbatch --job-name=combined_4n_12t --nodes=4 --cpus-per-task=12 combined.sbatch ./combined 12

sleep 30s

sbatch --job-name=combined_6n_2t --nodes=6 --cpus-per-task=2 combined.sbatch ./combined 2
sbatch --job-name=combined_6n_4t --nodes=6 --cpus-per-task=4 combined.sbatch ./combined 4
sbatch --job-name=combined_6n_6t --nodes=6 --cpus-per-task=6 combined.sbatch ./combined 6
sbatch --job-name=combined_6n_8t --nodes=6 --cpus-per-task=8 combined.sbatch ./combined 8
sbatch --job-name=combined_6n_10t --nodes=6 --cpus-per-task=10 combined.sbatch ./combined 10
sbatch --job-name=combined_6n_12t --nodes=6 --cpus-per-task=12 combined.sbatch ./combined 12

sleep 30s

sbatch --job-name=combined_8n_2t --nodes=8 --cpus-per-task=2 combined.sbatch ./combined 2
sbatch --job-name=combined_8n_4t --nodes=8 --cpus-per-task=4 combined.sbatch ./combined 4
sbatch --job-name=combined_8n_6t --nodes=8 --cpus-per-task=6 combined.sbatch ./combined 6
sbatch --job-name=combined_8n_8t --nodes=8 --cpus-per-task=8 combined.sbatch ./combined 8
sbatch --job-name=combined_8n_10t --nodes=8 --cpus-per-task=10 combined.sbatch ./combined 10
sbatch --job-name=combined_8n_12t --nodes=8 --cpus-per-task=12 combined.sbatch ./combined 12