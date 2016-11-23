
#include "mex.h"
#include "mpi.h"
#include <string.h>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	MPI_Status status;
	MPI_File fh;
	if(nrhs!=6) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","6 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	memcpy(&fh,mxGetData(prhs[0]),sizeof(MPI_File));
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_File_read_at(	fh,  /*file handle*/
													(MPI_Offset)mxGetScalar(prhs[1]),/* offset*/
													mxGetData(prhs[2]), /*buff*/
													(int)mxGetScalar(prhs[3]),  /*count*/
													*((MPI_Datatype *)mxGetData(prhs[4])),  /*datatype*/
													&status /*status*/
												));
/*
    *((int *)mxGetData(mxGetField(prhs[5],0,"count_lo")))=status.count_lo;
    *((int *)mxGetData(mxGetField(prhs[5],0,"count_hi_and_cancelled")))=status.count_hi_and_cancelled;
    *((int *)mxGetData(mxGetField(prhs[5],0,"MPI_SOURCE")))=status.MPI_SOURCE;
    *((int *)mxGetData(mxGetField(prhs[5],0,"MPI_TAG")))=status.MPI_TAG;
    *((int *)mxGetData(mxGetField(prhs[5],0,"MPI_ERROR")))=status.MPI_ERROR;
*/	
	nlhs=1;
	return; 
}
