
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","5 inputs required.");
	}
	if(nlhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}
    MPI_Win Win;
	plhs[0]=mxCreateDoubleScalar((double)MPI_Win_create(mxGetData(prhs[0]),     /* *baseptr*/
														  (MPI_Aint)mxGetScalar(prhs[1]),  /*size*/
														  (int)mxGetScalar(prhs[2]),  /*disp_unit*/
														  *((MPI_Aint *)mxGetData(prhs[3])), /*info*/
														  *((MPI_Comm *)mxGetData(prhs[4])), /*comm*/
														  &Win /*win*/
												));

    mexPrintf("\nWin is: %d\n",(double)Win);
    plhs[1] = mxCreateDoubleScalar(Win);
    mexPrintf("\nPlhs1 is : %d\n",mxGetScalar(plhs[1]));
	return; 
}
