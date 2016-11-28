addpath ../matlab
addpath ../octave
GetMPIEnvironment;
status=MPI_Status;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);
datatemp=0;

tic
for ii=1:1000
if(rank==0)
%	datatemp=1;
	err=MPI_Send(datatemp,1,MPI_DOUBLE,1,123,MPI_COMM_WORLD);
end
if(rank==1)
%	datatemp=0;
	err=MPI_Recv(datatemp,1,MPI_DOUBLE,0,123,MPI_COMM_WORLD,status);
  %  status
  %  datatemp
end
end
toc
err=MPI_Finalize;
exit
