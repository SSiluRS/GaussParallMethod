#!/bin/bash

#SBATCH --nodes=4
#SBATCH --ntasks-per-node=4
#SBATCH --job-name=mpi_openmp_task

cd $SLURM_SUBMIT_DIR

export OMP_NUM_THREADS=4

mpiexec -n 4 ./Program 1000

