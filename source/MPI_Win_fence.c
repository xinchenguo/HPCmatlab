
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
/*	double win = *mxGetPr(prhs[1]);*/
/*	MPI_Win win = (MPI_Win)mxGetScalar(prhs[1]);*/
/*	MPI_Win win = *w;*/
	if(nrhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","2 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	mexPrintf("\nWin in Fence : %d", (MPI_Win)mxGetScalar(prhs[1]) /*win*/);
	/* No support for asserts */	
	plhs[0]=mxCreateDoubleScalar((double)MPI_Win_fence(	
													(int)mxGetScalar(prhs[0]), /* assert */
													(MPI_Win)mxGetScalar(prhs[1]) /*win*/
												    ));

	return; 
}
