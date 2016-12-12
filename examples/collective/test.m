addpath ../../octave
%% This Matlab script demonstrates the use of MPI collective communication routines in HPCmatlab
GetMPIEnvironment;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
% The HPCmatlab MPI Environment is set up
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

N=32;               % Total length of array to be scattered
n=N/commsize;       % Number of elements that each process will receive
buff=zeros(1,n);    % Allocate the receive buffer on each process

if rank==0
    data=rand(1,N);       % Initialize data buffer to be scattered from root process
    disp('starting scatter');
    avg_check = mean(data);         % For validating the Reduce operation later
    tic
    err=MPI_Scatter(data, n, MPI_DOUBLE, buff, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);   % Scatter call on root process
end

if rank>0
    err=MPI_Scatter(0, n, MPI_DOUBLE, buff, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);      % Scatter call on other processes
end

disp(['filtering on rank' num2str(rank)]);
avg = mean(buff);
buff = buff - avg;       % Perform some operation on buffer on each process

% Now we want to gather the modified data back in rank order,
% but for some reason, we want it on all the processes now
% So, we will use MPI_Allgather instead of simply MPI_Gather

data=zeros(1,N);    % Allocate receive buffer on all processes
if rank==0
    disp('starting gather');
end
err=MPI_Allgather(buff, n, MPI_DOUBLE, data, n, MPI_DOUBLE, MPI_COMM_WORLD);        % MPI_Allgather call by all processes
clear buff

if rank==0
    data            % Print received array values on any of the processes (it should be same for all processes)
end

err=MPI_Barrier(MPI_COMM_WORLD);    % Synchronization to ensure output is not messed up

if rank==commsize-1
    data            % Print received array values on any of the processes (it should be same for all processes)
end

% We have also stored the mean of original values on each process in the variable 'avg'
% We now want to calculate the mean of all the values
% We will reduce the 'avg' variable on all processes to process 0, performing the MPI_SUM operation

avg_sum=0;          % Initialize buffer to receive reduced value (significant only at root process)
err=MPI_Reduce(avg, avg_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);            % MPI_Reduce call by all processes

if rank==0
    avg_all=avg_sum/commsize        % Calculate mean from sum
    avg_check                       % Validate using pre-calculated mean
    toc
end

err=MPI_Finalize;
exit
