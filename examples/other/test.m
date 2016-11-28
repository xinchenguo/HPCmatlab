addpath ../matlab
GetMPIEnvironment;
MPI_Status
MPI_Win
status=MPI_Status;
win = MPI_Win;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

recvtemp=3*ones(1,20);

datatemp=1:20;

err=MPI_Win_create(datatemp, 8*length(datatemp), 8, MPI_INFO_NULL, MPI_COMM_WORLD, win)

err=MPI_Win_fence(0,win);

if(rank==0)
    rank
    datatemp
    recvtemp
    err=MPI_Put(recvtemp, 20, MPI_DOUBLE, 1, 0, 20, MPI_DOUBLE, win);
end

err=MPI_Win_fence(0,win);

if(rank==1)
    datatemp
end

err=MPI_Win_free(win);
err=MPI_Finalize;
exit
