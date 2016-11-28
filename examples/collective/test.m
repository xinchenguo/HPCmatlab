
%% This Matlab script demonstrates the use of MPI collective communication routines in HPCmatlab
GetMPIEnvironment;
%commsize=0;
%rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
% The HPCmatlab MPI Environment is set up
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);
err=MPI_Barrier(MPI_COMM_WORLD);    % Synchronization to ensure output is not messed up
N=32;               % Total length of array to be scattered
n=N/commsize;       % Number of elements that each process will receive
buff=zeros(1,n);    % Allocate the receive buffer on each process

if rank==0
    data=rand(1,N);       % Initialize data buffer to be scattered from root process
    disp(['Actual Data: ' num2str(data)]);
    disp('starting scatter');
    avg_check = mean(data);         % For validating the Reduce operation later
    tic
    err=MPI_Scatter(data, n, MPI_DOUBLE, buff, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);   % Scatter call on root process
end

if rank>0
    err=MPI_Scatter(0, n, MPI_DOUBLE, buff, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);      % Scatter call on other processes
end
disp(['I am rank ' num2str(rank) ' buff is:  ' num2str(buff)]);
%disp(['filtering on rank ' num2str(rank)]);
avg = mean(buff);
buff = buff - avg;       % Perform some operation on buffer on each process

% Now we want to gather the modified data back in rank order,
% but for some reason, we want it on all the processes now
% So, we will use MPI_Allgather instead of simply MPI_Gather

%data=zeros(1,N);    % Allocate receive buffer on all processes
if rank==0
    disp('starting gather');
end
disp(['I am rank ' num2str(rank) ' buff is:  ' num2str(buff)]);
[err,recv_buff]=MPI_Alltoall(buff, n/commsize, MPI_DOUBLE, n/commsize, MPI_DOUBLE, MPI_COMM_WORLD);        % MPI_Allgather call by all processes
clear buff

err=MPI_Barrier(MPI_COMM_WORLD);    % Synchronization to ensure output is not messed up

%disp(['I am rank ' num2str(rank) ' recv_buff is:  ' num2str(recv_buff)]);         % Print received array values on any of the processes (it should be same for all processes)
recv_buff
% We have also stored the mean of original values on each process in the variable 'avg'
% We now want to calculate the mean of all the values
% We will reduce the 'avg' variable on all processes to process 0, performing the MPI_SUM operation

avg_sum=0;          % Initialize buffer to receive reduced value (significant only at root process)
disp(['I am rank ' num2str(rank) ' avg is: ' num2str(avg)]);

[err,avg_sum]=MPI_Allreduce(avg, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);            % MPI_Reduce call by all processes

%if rank==0
    avg_sum
    avg_all=avg_sum/commsize;        % Calculate mean from sum
    avg_all
if rank == 0
    avg_check                       % Validate using pre-calculated mean
    toc
end

err=MPI_Finalize;
exit

