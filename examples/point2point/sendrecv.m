%% This Matlab script shows how to use HPCmatlab routine for COMBINED send and receive

% Set up HPCmatlab MPI Environment
GetMPIEnvironment;
status=MPI_Status;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

N=5;
tag1=123;
tag2=456;
% We will send data from rank '0' to rank '1' as well as '1' to '0'
if rank==0
    data=1:N;
    recv_buff=zeros(1,N);
    err=MPI_Sendrecv(data,N,MPI_DOUBLE,1,tag1,recv_buff,N,MPI_DOUBLE,1,tag2,MPI_COMM_WORLD,status);
    disp('After sendrecv communication, on rank 0:');
    recv_buff
end

if rank==1
    data=(1:N)*2;
    recv_buff=zeros(1,N);
    err=MPI_Sendrecv(data,N,MPI_DOUBLE,0,tag2,recv_buff,N,MPI_DOUBLE,0,tag1,MPI_COMM_WORLD,status);
    disp('After sendrecv communication, on rank 1:');
    recv_buff
end

% Finalize MPI and exit Matlab
err=MPI_Finalize;
exit
