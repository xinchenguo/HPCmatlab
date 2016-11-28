
# HPCmatlab software framework

About HPCmatlab
---------------

HPCmatlab is a framework for fast prototyping of parallel applications on Matlab.
It uses the Message Passing Interface (MPI) for sending and receiving messages among
different Matlab processes. The users can use mex functions with syntax similar 
to the MPI standard syntax.


Version 1.0
-----------

This version includes our MPI functions.


Documentation
-------------

The User Guide for this version is included in form of the PDF file
"HPCmatlab_1.0_User_Guide.pdf" under `doc/`

For users new to parallel programming, we recommend trying out the simple 
send-receive examples first to get started with the framework.

For details on implementation and performance results, refer our conference paper 
also under `doc/`

URL: http://www.sciencedirect.com/science/article/pii/S1877050916309516


Examples
--------

The examples of simple programs using point-to-point, collective and one-sided 
communications are included under `examples/` directory.
They also have sample job submission files for SLURM.


Installation and Use
--------------------

GitHub download page: https://github.com/xinchenguo/HPCmatlab

1. Make sure Matlab's `mex` compiler is in your $PATH.
Also, `mpicc` and `mpicxx` should be in $PATH with all environment variables set up 
for MPI libraries.

2. Run `make` to compile the MEX functions from source code.
The MEX functions will be placed under `matlab/` directory.

3. There are two ways to add the path to these functions to Matlab's search path:

  * Before running your script, set the `MATLABPATH` environment variable, e.g.
  
  `export MATLABPATH=/path/to/HPCmatlab/matlab:$MATLABPATH`

  * At the start of your Matlab script, use Matlab's `addpath` function.
Refer examples for how to do this.


Contact
-------

Use our GitHub page for questions, bug reports, comments, feedback and suggestions:

https://github.com/xinchenguo/HPCmatlab/issues
