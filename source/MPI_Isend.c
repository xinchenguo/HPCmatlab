
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=6) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","6 inputs required.");
	}
	if(nlhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}
	MPI_Request request;
	plhs[0]=mxCreateDoubleScalar((double)MPI_Isend(	mxGetData(prhs[0]),  
													(int)mxGetScalar(prhs[1]), 
													*((MPI_Datatype *)mxGetData(prhs[2])), 
													(int)mxGetScalar(prhs[3]),  
													(int)mxGetScalar(prhs[4]), 
													*((MPI_Comm *)mxGetData(prhs[5])),
													&request
												));	
	plhs[1] = mxCreateDoubleScalar((double)request);
	return; 
}
