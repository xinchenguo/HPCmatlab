%% This Matlab script shows how to use HPCmatlab routines for NON-BLOCKING send and receive of data

% Set up HPCmatlab MPI Environment
addpath ../../octave
GetMPIEnvironment;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

N=5;
tag1=123;
tag2=456;
%req1=zeros(1,1,'int32');   %% For octave
%req2=zeros(1,1,'int32');
req1=MPI_Request;
req2=MPI_Request;
status1=MPI_Status;
status2=MPI_Status;
% We will send data from rank '0' to rank '1' as well as from '1' to '0'
% The order of communication calls as below would have resulted in a deadlock had we used blocking calls
if rank==0
    data=1:N;
    recv_buff=zeros(1,N);
    err=MPI_Irecv(recv_buff,N,MPI_DOUBLE,1,tag2,MPI_COMM_WORLD,req2);
    err=MPI_Isend(data,N,MPI_DOUBLE,1,tag1,MPI_COMM_WORLD,req1);
    err=MPI_Waitall(2,[req1;req2],[status1;status2]);
    disp('After communication, on rank 0:');
    recv_buff
end

if rank==1
    data=(1:N)*2;
    recv_buff=zeros(1,N);
    disp('Before communication:');
    recv_buff
    err=MPI_Irecv(recv_buff,N,MPI_DOUBLE,0,tag1,MPI_COMM_WORLD,req1);
    err=MPI_Isend(data,N,MPI_DOUBLE,0,tag2,MPI_COMM_WORLD,req2);
    err=MPI_Waitall(2,[req1;req2],[status1;status2]);
    disp('After communication, on rank 1:');
    recv_buff
end

% Finalize MPI and exit Matlab
err=MPI_Finalize;
exit
