%% This Matlab script shows how to use HPCmatlab routines for BUFFERED sending and receiving of data

% Set up HPCmatlab MPI Environment
GetMPIEnvironment;
%status=MPI_Status;
%commsize=0;
%rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

N=5;
tag=123;
    send_buffer=zeros(1,100);
    err=MPI_Buffer_attach(send_buffer,8*length(send_buffer))

% We will send data from rank '0' to rank '1'
if rank==1
    % Initialize buffer (array) on rank 1 which will receive data
    %recv_buff=zeros(1,N);
    err=MPI_Barrier(MPI_COMM_WORLD);
    %disp('Before communication:');
    %recv_buff
    % Now receive 20 'double' type elements from rank '0'
    [err,recv_buff,status]=MPI_Recv(N,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);
    disp('After communication:');
    recv_buff
   disp('Program completed');
end

if rank==0
    data=1:N;
    err=MPI_Barrier(MPI_COMM_WORLD);

    err=MPI_Bsend(data,N,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
end
    [err,send_buffer_detach,send_buffer_length]=MPI_Buffer_detach();


% Finalize MPI and exit Matlab
err=MPI_Finalize;
exit
