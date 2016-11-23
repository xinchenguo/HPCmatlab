/*
 *  This mex function returns the communicator MPI_COMM_WORLD
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int MPI_CommSize=0;
	
	MPI_CommSize=sizeof(MPI_Comm);
	if(sizeof(MPI_Comm)==1)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT8_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==2)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT16_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==4)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==8)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	nlhs=1;		

	return;
}
