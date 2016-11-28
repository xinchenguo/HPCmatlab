#!/bin/bash
#SBATCH -n 2
#SBATCH -t 00:07:00
#SBATCH -o test.out
#SBATCH -e test.err
module load intel-mpi/5.0
module load matlab/2016a
export MATLABPATH=../../matlab
srun -n 2 --mpi=pmi2 matlab -r "itest,exit"
