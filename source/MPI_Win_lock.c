
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=4) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","4 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
/* No support for asserts */	
	mexPrintf("\n the rank inside mex lock: %d\n",(int)mxGetScalar(prhs[1]));
	mexPrintf("\n the win inside mex lock: %d\n",(int)mxGetScalar(prhs[3]));
	plhs[0]=mxCreateDoubleScalar((double)MPI_Win_lock(	
													(int)mxGetScalar(prhs[0]), /* lock_type */
													(int)mxGetScalar(prhs[1]), /* rank */
													(int)mxGetScalar(prhs[2]), /* assert */
													(MPI_Win)mxGetScalar(prhs[3]) /*win*/
												));

	nlhs=1;
	return; 
}
