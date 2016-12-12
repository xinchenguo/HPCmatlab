#!/bin/bash
#SBATCH -n 2
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load matlab/R2014a
export MATLABPATH=../../matlab
mpirun -n 2 matlab -r "itest,exit"
