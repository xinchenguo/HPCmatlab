
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /*  double *w = mxGetPr(prhs[0]);*/
    MPI_Win win = mxGetScalar(prhs[0]);
	if(nrhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","1 inputs required.");
	}   
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_Win_free( &win /*win*/
												    ));
	return; 
}
