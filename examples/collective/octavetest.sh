#!/bin/bash
#SBATCH -n 8
#SBATCH -t 00:15:00
#SBATCH -o test.out
#SBATCH -e test.err
module load octave/4.0.0
mpirun -n 8 octave test.m
