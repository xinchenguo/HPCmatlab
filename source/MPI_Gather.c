
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=8) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","8 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	plhs[0]=mxCreateDoubleScalar((double)MPI_Gather(	mxGetData(prhs[0]),  
													(int)mxGetScalar(prhs[1]), 
													*((MPI_Datatype *)mxGetData(prhs[2])),
													mxGetData(prhs[3]),
													(int)mxGetScalar(prhs[4]),
													*((MPI_Datatype *)mxGetData(prhs[5])),
                                                    (int)mxGetScalar(prhs[6]),
													*((MPI_Comm *)mxGetData(prhs[7])) 
												));							
	nlhs=1;
	return;
}
