#!/bin/bash
#SBATCH -n 3
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load mvapich2/2.1-gnu-4.9.2
module load matlab/2016a
export MATLABPATH=${MATLABPATH}:../../matlab
srun -n 2 --mpi=pmi2 matlab -r "alloc_test,exit"
