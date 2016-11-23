
#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	
	MPI_Status status;
	mexPrintf("validation");
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","5 inputs required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","3 output required.");
	}
	mexPrintf("Creating buff");
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

	int m =1,n =1;
        int nfields = 5;
        const char *fieldnames[] =                      {                       "count_lo",
                                                                "count_hi_and_cancelled",
                                                                "MPI_SOURCE",
                                                                "MPI_TAG",
                                                                "MPI_ERROR"     };
	mexPrintf("trying to create struct matrix\n");
        plhs[2] = mxCreateStructMatrix(m, n, nfields, fieldnames);
	mexPrintf("Struct Matrix created\n");
	plhs[0]=mxCreateDoubleScalar((double)MPI_Recv(							mxGetData(plhs[1]),  /*buff*/
													(int)mxGetScalar(prhs[0]),  /* count */
													*((MPI_Datatype *)mxGetData(prhs[1])),  /*datatype*/
													(int)mxGetScalar(prhs[2]),  /*source*/
													(int)mxGetScalar(prhs[3]), /*tag*/
													*((MPI_Comm *)mxGetData(prhs[4])), /*comm*/
													&status /*status*/
	

												));

	mxSetFieldByNumber(plhs[2],0,0,mxCreateDoubleScalar((double)status.count_lo));
	mxSetFieldByNumber(plhs[2],0,1,mxCreateDoubleScalar((double)status.count_hi_and_cancelled));
	mxSetFieldByNumber(plhs[2],0,2,mxCreateDoubleScalar((double)status.MPI_SOURCE));
	mxSetFieldByNumber(plhs[2],0,3,mxCreateDoubleScalar((double)status.MPI_TAG));
	mxSetFieldByNumber(plhs[2],0,4,mxCreateDoubleScalar((double)status.MPI_ERROR));	
	
	return; 
}
