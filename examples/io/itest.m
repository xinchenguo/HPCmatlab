addpath('../../octave');
GetMPIEnvironment
request1=MPI_Request;
request2 = MPI_Request;
status=MPI_Status;
fh=MPI_File;
commsize=0;
rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank)...
    ' out of ' num2str(commsize)]);

err = MPI_File_open(MPI_COMM_WORLD, 'trial',...
bitor(MPI_MODE_RDWR,MPI_MODE_CREATE), MPI_INFO_NULL, fh);

n = 10;
a = rand(n,1);

err = MPI_File_set_size(fh, n*n*commsize*8);

offset = n*n*rank*8;

[err,request1] = MPI_File_iwrite_at(fh, offset, a,...
n*n, MPI_DOUBLE);

c = rand(1,1);
%ans1 = c*a;
a
%b = zeros(n,1);

[err,status] = MPI_Waitall(1,request1);

[err, b, request2] = MPI_File_iread_at(fh, offset, n*1, MPI_DOUBLE);
[err,status] = MPI_Waitall(1,[request1,request2]);
b
%ans2 = c*b;

%nnz(~(ans1==ans2))

err = MPI_File_close(fh);

err = MPI_Finalize;
exit
