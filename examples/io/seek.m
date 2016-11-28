addpath('../../octave');
GetMPIEnvironment
status=MPI_Status;
fh=MPI_File;
commsize=0;
rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

err = MPI_File_open(MPI_COMM_WORLD, 'trial', bitor(MPI_MODE_RDWR,MPI_MODE_CREATE), MPI_INFO_NULL, fh);

n=5;
a = n*rank+1:n*(rank+1);

offset = n*rank*8;

err = MPI_File_seek(fh, offset, MPI_SEEK_SET);
err = MPI_File_write(fh, a, n, MPI_DOUBLE, status);
b = zeros(n,1);

offset = -n*8;
err = MPI_File_seek(fh, offset, MPI_SEEK_CUR);
err = MPI_File_read(fh, b, n, MPI_DOUBLE, status);

b

err = MPI_File_close(fh);

err = MPI_Finalize;
exit
