%% This Matlab script shows how to use HPCmatlab routines for NON-BLOCKING send and receive of data

% Set up HPCmatlab MPI Environment
addpath('../../matlab');
GetMPIEnvironment;
%commsize=0;
%rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

N=5;
tag1=123;
tag2=456;
%req1=zeros(1,1,'int32');   %% For octave
%req2=zeros(1,1,'int32');
%req1=MPI_Request;
%req2=MPI_Request;
%status1=MPI_Status;
%status2=MPI_Status;
% We will send data from rank '0' to rank '1' as well as from '1' to '0'
% The order of communication calls as below would have resulted in a deadlock had we used blocking calls
%statusArray = [status1;status2];
if rank==0
    data=1:N;
    recv_buff=zeros(1,N);
    recv_copy1 = recv_buff;
    [err,recv_buff,req2]=MPI_Irecv(N,MPI_DOUBLE,1,tag2,MPI_COMM_WORLD);
    [err,req1]=MPI_Isend(data,N,MPI_DOUBLE,1,tag1,MPI_COMM_WORLD);
    req1
    req2
    [err,statusArray]=MPI_Waitall(2,[req1;req2]);
    disp('After communication, on rank 0:');
    recv_buff
    recv_copy1
end

if rank==1
    data=(1:N)*2;
    recv_buff=zeros(1,N);
    disp('Before communication:');
    recv_buff
      recv_copy2 = recv_buff;
    [err,recv_buff,req2]=MPI_Irecv(N,MPI_DOUBLE,0,tag1,MPI_COMM_WORLD);
    [err,req1]=MPI_Isend(data,N,MPI_DOUBLE,0,tag2,MPI_COMM_WORLD);
   
    disp('Running Waitall:');
    [err,statusArray]=MPI_Waitall(2,[req1;req2]);
    disp('After communication, on rank 1:');
    recv_buff
    recv_copy2
end

% Finalize MPI and exit Matlab
err=MPI_Finalize;
exit
