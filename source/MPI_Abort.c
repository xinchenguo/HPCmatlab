
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","2 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	plhs[0]=mxCreateDoubleScalar((double)MPI_Abort(*((MPI_Comm *)mxGetData(prhs[0])),
													(int)mxGetScalar(prhs[1])
													));							
	nlhs=1;
	return;
}
