
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int rank,size;
	if(nrhs!=0) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","0 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	plhs[0]=mxCreateDoubleScalar((double)MPI_Finalize());
	nlhs=1;
	return;
}
