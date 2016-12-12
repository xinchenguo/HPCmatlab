addpath ../../octave
%% This Matlab script shows how to use HPCmatlab routines for sending and receiving data among different processes

% Set up HPCmatlab MPI Environment
GetMPIEnvironment;
% Define the special 'struct' that would be required using an assignment operation as below
% Here, MPI_Status is a standard struct type for storing the status of a communication call like MPI_Recv
% 'status' is a specific instance of that type which will be used in this script
status=MPI_Status;
% Initialize variables to store the process rank and size of the communicator (total number of processes)
% If the number of processes are 'n', then the ranks range from '0' to 'n-1'
commsize=0;
rank=0;
% Initialize MPI; Currently MPI_Init does not support any arguments, so just pass (0,0)
err=MPI_Init(0,0);
% Get the size of MPI communicator and rank of the process
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
% Display the rank
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);
N=5;
tag=123;
% We will send data from rank '0' to rank '1'
if rank==0
    data=1:N;
    err=MPI_Barrier(MPI_COMM_WORLD);
    err=MPI_Send(data,N,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
end

if rank==1
    % Initialize buffer (array) on rank 1 which will receive data
    recv_buff=zeros(1,N);
    disp('Before communication:');
    recv_buff
    err=MPI_Barrier(MPI_COMM_WORLD);
    % Now receive N 'double' type elements from rank '0'
    err=MPI_Recv(recv_buff,N,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,status);
    disp('After communication:');
    recv_buff
end

% Finalize MPI and exit Matlab
err=MPI_Finalize;
exit
