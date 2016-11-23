
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
     switch(*((MPI_Datatype *)mxGetData(prhs[2])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxDOUBLE_CLASS,mxREAL);
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxSINGLE_CLASS,mxREAL);
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxINT16_CLASS,mxREAL);
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}

	plhs[0]=mxCreateDoubleScalar((double)MPI_Allreduce(	mxGetData(prhs[0]),
													mxGetData(plhs[1]),
													(int)mxGetScalar(prhs[1]), 
													*((MPI_Datatype *)mxGetData(prhs[2])), 
													*((MPI_Op *)mxGetData(prhs[3])), 
													*((MPI_Comm *)mxGetData(prhs[4])) 
												));							
	nlhs=1;
	return;
}
