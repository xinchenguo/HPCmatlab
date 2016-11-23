
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
/*	double *w = mxGetPr(prhs[7]);*/
        MPI_Win win = mxGetScalar(prhs[7]);
	if(nrhs!=8) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","8 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
    mexPrintf("\nWin in Get : %d", win /*win*/);	
	mexPrintf("\nData in get :%d\n",mxGetScalar(prhs[0]));
    plhs[0]=mxCreateDoubleScalar((double)MPI_Get(	mxGetData(prhs[0]),  /*origin_addr*/
													(int)mxGetScalar(prhs[1]),  /*origin_count */
													*((MPI_Datatype *)mxGetData(prhs[2])),  /*origin_datatype*/
													(int)mxGetScalar(prhs[3]),  /*target_rank*/
													*((MPI_Aint *)mxGetData(prhs[4])), /*target_disp*/
													(int)mxGetScalar(prhs[5]),  /*target_count*/
													*((MPI_Datatype *)mxGetData(prhs[6])),  /*target_datatype*/
													win /*win*/
												));
	mexPrintf("\nData in get :%d\n",mxGetScalar(prhs[0]));
	return; 
}
