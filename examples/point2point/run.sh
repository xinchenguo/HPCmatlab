#!/bin/bash
srun -n 2 --mpi=pmi2 matlab -r "test,exit"
