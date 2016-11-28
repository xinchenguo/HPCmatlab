#!/bin/bash
#SBATCH -n 4
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load matlab/2015b
module load intel-mpi/5.0
export MATLABPATH=${MATLABPATH}:../../matlab
srun -n 2 --mpi=pmi2 matlab -r "itest,exit"
