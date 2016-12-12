#!/bin/bash
#SBATCH -n 3
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load matlab/R2014a
export MATLABPATH=${MATLABPATH}:../../matlab
mpirun -n 3 matlab -r "lock_test,exit"
