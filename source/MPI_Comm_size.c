
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int size;
	MPI_Comm commtemp;
	if(nrhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","1 inputs required.");
	}
	if(nlhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}
	commtemp=*((MPI_Comm *)mxGetData(prhs[0]));
	plhs[0]=mxCreateDoubleScalar((double)MPI_Comm_size(commtemp,&size));
	plhs[1]=mxCreateDoubleScalar((double)size);
	
	return;
}
