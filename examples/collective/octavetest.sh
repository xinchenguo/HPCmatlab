#!/bin/bash
#SBATCH -n 8
#SBATCH -t 00:15:00
#SBATCH -o test.out
#SBATCH -e test.err
module load octave/4.0.0
srun -n 8 --mpi=pmi2 octave test.m
