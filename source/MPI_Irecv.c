
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","6 inputs required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}

	 switch(*((MPI_Datatype *)mxGetData(prhs[1])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxDOUBLE_CLASS,mxREAL);
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxSINGLE_CLASS,mxREAL);
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxINT16_CLASS,mxREAL);
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}
     MPI_Request request;
     plhs[0]=mxCreateDoubleScalar((double)MPI_Irecv(							mxGetData(plhs[1]),  
													(int)mxGetScalar(prhs[0]), 
													*((MPI_Datatype *)mxGetData(prhs[1])), 
													(int)mxGetScalar(prhs[2]),  
													(int)mxGetScalar(prhs[3]), 
													*((MPI_Comm *)mxGetData(prhs[4])),
													 &request
												));
	plhs[2] = mxCreateDoubleScalar((double)request);
	return; 
}
