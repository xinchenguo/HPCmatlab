
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=6) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","6 inputs required.");
	}
	if(nlhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}
     switch(*((MPI_Datatype *)mxGetData(prhs[4])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[3])*2,1,mxDOUBLE_CLASS,mxREAL);
        mexPrintf("\nDouble\n");
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[3]),1,mxSINGLE_CLASS,mxREAL);
        mexPrintf("\nFloat\n");
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[3]),1,mxINT16_CLASS,mxREAL);
        mexPrintf("\nInt\n");
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}
    mexPrintf("\nstarting All to all\n");
	plhs[0]=mxCreateDoubleScalar((double)MPI_Alltoall(	mxGetData(prhs[0]),  
													(int)mxGetScalar(prhs[1]), 
													*((MPI_Datatype *)mxGetData(prhs[2])),
													mxGetData(plhs[1]),
													(int)mxGetScalar(prhs[3]),
													*((MPI_Datatype *)mxGetData(prhs[4])),
													*((MPI_Comm *)mxGetData(prhs[5])) 
												));							
	nlhs=1;
	return;
}
