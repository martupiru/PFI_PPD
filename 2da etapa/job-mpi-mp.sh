#!/bin/bash
#SBATCH --job-name=matrizHibrida
#SBATCH --output=hybrid_%j.txt
#SBATCH --error=hybrid_error_%j.txt

#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=2

#SBATCH --partition=short
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

mpirun ./paralelo-mpi-mp 5000 5000 5000