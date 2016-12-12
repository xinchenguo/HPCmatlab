#!/bin/bash
#SBATCH -n 4
#SBATCH -t 00:05:00
#SBATCH -o test.out
#SBATCH -e test.err
module load matlab/R2014a
export MATLABPATH=${MATLABPATH}:../../matlab
mpirun -n 4 matlab -r "seek,exit"
