
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int size;
	if(nrhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","1 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	plhs[0]=mxCreateDoubleScalar((double)MPI_Barrier(*((MPI_Comm *)mxGetData(prhs[0]))));
	nlhs=1;
	return;
}
