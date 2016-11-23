/*
 *  This mex function allocates and returns special MPI type handles
 */

#include "mex.h"
#include "mpi.h"
#define N 8
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int Size[N],ii;
	Size[0]=sizeof(MPI_Count);
	Size[1]=sizeof(int);
	Size[2]=sizeof(MPI_Request);
    Size[3]=sizeof(MPI_Win);
    Size[4]=sizeof(MPI_Datatype);
    Size[5]=sizeof(MPI_Aint);
    Size[6]=sizeof(MPI_Info);
    Size[7]=sizeof(MPI_Offset);
	for(ii=0;ii<N;ii++)
	{
		if(Size[ii]==1)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT8_CLASS,mxREAL);
			*((int8_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==2)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT16_CLASS,mxREAL);
			*((int16_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==4)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
			*((int32_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==8)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
			*((int64_T *)mxGetData(plhs[ii]))=0;
		}
	}
	nlhs=N;		
	

	return;
}
