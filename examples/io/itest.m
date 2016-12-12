% Non-blocking read-write example using the HPCmatlab framework
addpath('../../octave');
GetMPIEnvironment
request=MPI_Request;
status=MPI_Status;
fh=MPI_File;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank)...
    ' out of ' num2str(commsize)]);

err = MPI_File_open(MPI_COMM_WORLD, 'trial',...
bitor(MPI_MODE_RDWR,MPI_MODE_CREATE), MPI_INFO_NULL, fh);

n = 1024;
a = rand(n,n);

err = MPI_File_set_size(fh, n*n*commsize*8);

offset = n*n*rank*8;

err = MPI_File_iwrite_at(fh, offset, a,...
n*n, MPI_DOUBLE, request);

c = rand(n,n);
ans1 = c*a;

b = zeros(n,n);

err = MPI_Waitall(1,request,status);

err = MPI_File_iread_at(fh, offset, b, n*n, MPI_DOUBLE, request);
err = MPI_Waitall(1,request,status);

ans2 = c*b;

nnz(~(ans1==ans2))  % should be zero

err = MPI_File_close(fh);

err = MPI_Finalize;
exit
