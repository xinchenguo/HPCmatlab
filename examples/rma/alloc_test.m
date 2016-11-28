% This example shows using MPI one-sided communication calls from the HPCmatlab framework
addpath ../../matlab
GetMPIEnvironment;
% Initialize a MPI Window object
%win = MPI_Win;
%commsize=0;
%rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

n=1;
bytes=8*n*n;        % 8 bytes per element for 'double'
data=0;
%[err,win]=MPI_Win_allocate(bytes, 8, MPI_INFO_NULL, MPI_COMM_WORLD,data);

if rank==0
    [err,win]=MPI_Win_allocate(bytes, 8, MPI_INFO_NULL, MPI_COMM_WORLD,data);
    disp(['at rank' num2str(rank) 'data is ' num2str(data)]);
    for j=1:n
        for i=1:n
            data(i,j)=data(i,j)+n*(j-1)+i;
        end
    end
    disp('On rank 0:');
    data
    err=MPI_Win_fence(0,win);
    err=MPI_Win_fence(0,win);
end

if rank==1
    [err,win]=MPI_Win_allocate(bytes, 8, MPI_INFO_NULL, MPI_COMM_WORLD,data);
    err=MPI_Win_fence(0,win);
    disp('At rank 1, before Get from 0:');
    data
    err=MPI_Get(data, n*n, MPI_DOUBLE, 0, 0, n*n, MPI_DOUBLE, win);
    err=MPI_Win_fence(0,win);
    disp('At rank 1, after Get from 0');
    data
end

err=MPI_Win_free(win);
err=MPI_Finalize;
exit
