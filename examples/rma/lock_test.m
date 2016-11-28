addpath ../../octave
% This example shows using MPI one-sided communication using LOCKS
GetMPIEnvironment;
% Initialize a MPI Window object
win = MPI_Win;
%commsize=0;
%rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

n=5;
data=int32(zeros(n,n));
bytes=4*n*n;        % 4 bytes per element for 'int32'

% We will first Put data from rank '2' to rank '0' and then Get that data on rank '1' from rank '0'
if rank==0
    for j=1:n
        for i=1:n
            data(i,j)=n*(j-1)+i;
        end
    end
    disp('On rank 0:');
    data
    [err,win]=MPI_Win_create(data, bytes, 4, MPI_INFO_NULL, MPI_COMM_WORLD);
    err=MPI_Barrier(MPI_COMM_WORLD);
end

if rank==1
    [err,win]=MPI_Win_create(0, 0, 4, MPI_INFO_NULL, MPI_COMM_WORLD);
    err=MPI_Barrier(MPI_COMM_WORLD);
    win
    err=MPI_Win_lock(MPI_LOCK_EXCLUSIVE,0,0,win);
    disp('At rank 1, before Get from 0:');
    data
    err=MPI_Get(data, n*n, MPI_INT, 0, 0, n*n, MPI_INT, win);
    err=MPI_Win_unlock(0,win);
    disp('At rank 1, after Get from 0');
    data
end

if rank==2
    [err,win]=MPI_Win_create(0, 0, 4, MPI_INFO_NULL, MPI_COMM_WORLD);
    data(:,:)=1;
    err=MPI_Win_lock(MPI_LOCK_EXCLUSIVE,0,0,win);
    err=MPI_Put(data, n*n, MPI_INT, 0, 0, n*n, MPI_INT, win);
    err=MPI_Win_unlock(0,win);
    err=MPI_Barrier(MPI_COMM_WORLD);
end

err=MPI_Win_free(win);
err=MPI_Finalize;
exit
