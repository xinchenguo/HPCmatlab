/*
 *  Currently does not support arguments
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int rank,size;
	if(nrhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","2 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	plhs[0]=mxCreateDoubleScalar((double)MPI_Init(0,0));
	nlhs=1;
	return;
}
