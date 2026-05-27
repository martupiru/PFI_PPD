#!/bin/bash
#SBATCH --job-name=matrizHibrida
#SBATCH --output=salida_%j.txt
#SBATCH --error=error_%j.txt

#SBATCH --nodes=14

#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4

#SBATCH --time=01:00:00

module load gcc
module load openmpi

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

echo "=================================="
echo "JOB MPI + OPENMP"
echo "=================================="

echo "Nodos: $SLURM_JOB_NUM_NODES"
echo "MPI tasks: $SLURM_NTASKS"
echo "Threads OpenMP: $OMP_NUM_THREADS"

mpirun ./paralelo-mpi-mp