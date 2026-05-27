#!/bin/bash
#SBATCH --job-name=matrizMPI
#SBATCH --output=salida_%j.txt
#SBATCH --error=error_%j.txt

#SBATCH --nodes=14
#SBATCH --ntasks-per-node=16

#SBATCH --cpus-per-task=1

#SBATCH --time=01:00:00

echo "=================================="
echo "JOB MPI"
echo "=================================="

echo "Nodos: $SLURM_JOB_NUM_NODES"
echo "Tasks totales: $SLURM_NTASKS"

module load gcc
module load openmpi

mpirun ./paralelo-mpi