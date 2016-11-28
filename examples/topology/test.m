addpath('../../octave');
GetMPIEnvironment
cart_comm=GetMPICOMMWORLD;
commsize=0;
rank=0;
err=MPI_Init(0,0);
err=MPI_Comm_size(MPI_COMM_WORLD,commsize);
err=MPI_Comm_rank(MPI_COMM_WORLD,rank);
disp(['I am rank ' num2str(rank) ' out of ' num2str(commsize)]);

dims = [3 3];
periodic = [0 0];
reorder = 0;

err = MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, reorder, cart_comm);

coords=[0 0];
err = MPI_Cart_coords(cart_comm, rank, 2, coords);

disp(['I am rank ' num2str(rank) ' and my coordinates are ' num2str(coords(1)) ' , ' num2str(coords(2))]);

err = MPI_Finalize;
exit
