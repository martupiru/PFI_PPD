#!/bin/bash
#SBATCH --job-name=matrizMPI
#SBATCH --output=mpi_%j.txt
#SBATCH --error=mpi_error_%j.txt

#SBATCH --nodes=1
#SBATCH --ntasks=8
#SBATCH --cpus-per-task=1

#SBATCH --partition=short
#SBATCH --time=01:00:00

module load gcc
module load openmpi

echo "=================================="
echo "JOB MPI"
echo "=================================="

echo "Nodos: $SLURM_JOB_NUM_NODES"
echo "Tasks totales: $SLURM_NTASKS"

mpirun ./paralelo-mpi 5000 5000 5000