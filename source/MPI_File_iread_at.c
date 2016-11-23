
#include "mex.h"
#include "mpi.h"
#include <string.h>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	MPI_File fh;
	if(nrhs!=4) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","4 inputs required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","3 output required.");
	}
    
     switch(*((MPI_Datatype *)mxGetData(prhs[3])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[2]),1,mxDOUBLE_CLASS,mxREAL);
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[2]),1,mxSINGLE_CLASS,mxREAL);
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[2]),1,mxINT16_CLASS,mxREAL);
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}



	memcpy(&fh,mxGetData(prhs[0]),sizeof(MPI_File));
    MPI_Request request;
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_File_iread_at(	fh,  /*file handle*/
													(MPI_Offset)mxGetScalar(prhs[1]),/* offset*/
													mxGetData(plhs[1]), /*buff*/
													(int)mxGetScalar(prhs[2]),  /*count*/
													*((MPI_Datatype *)mxGetData(prhs[3])),  /*datatype*/
												/*	(MPI_Request *)mxGetData(prhs[5]) * request */
                                                    &request
												));
    plhs[2] = mxCreateDoubleScalar((double)request);
	nlhs=1;
	return; 
}
