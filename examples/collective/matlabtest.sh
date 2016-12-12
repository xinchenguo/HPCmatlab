#!/bin/bash
#SBATCH -n 8
#SBATCH -t 00:15:00
#SBATCH -o test.out
#SBATCH -e test.err
module load matlab/R2014a
export MATLABPATH=${MATLABPATH}:../../matlab
mpirun -n 8 matlab -r "test,exit"
