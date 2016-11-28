%addpath('../../matlab');
GetMPIEnvironment
status=MPI_Status;
fh=MPI_File;
commsize=0;
rank=0;
err=MPI_Init(0,0);
[err,commsize]=MPI_Comm_size(MPI_COMM_WORLD);
[err,rank]=MPI_Comm_rank(MPI_COMM_WORLD);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

% Create a file and open
err = MPI_File_open(MPI_COMM_WORLD, 'trial', bitor(MPI_MODE_RDWR,MPI_MODE_CREATE), MPI_INFO_NULL, fh);

n=5;
a = n*rank+1:n*(rank+1);     % Buffer from which to write data
a=a'

err = MPI_File_set_size(fh, n*commsize*8);      % Set size of file in bytes

offset = n*rank*8;

err = MPI_File_write_at(fh, offset, a, n, MPI_DOUBLE, status);  % Write data

b = zeros(n,1);     % Buffer to read data from file

err = MPI_File_read_at(fh, offset, b, n, MPI_DOUBLE, status);   % Read

b

err = MPI_File_close(fh);   % Close file

err = MPI_Finalize;
exit
