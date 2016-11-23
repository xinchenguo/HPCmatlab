#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs!=0) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","no input required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","3 output required.");
	}

/* MPI_Buffer_detach takes the address of the pointer as the first argument instead of the pointer itself */

    void *buff;
    /*buff=(void *)mxGetData(plhs[1]);*/
    int size;/*= (int *)mxGetPr(plhs[2]);*/
	plhs[0]=mxCreateDoubleScalar((double)MPI_Buffer_detach(	
													&buff,
													&size
													));	
        double *d = (double *)buff;
	mexPrintf("\nBuff:\t%d\t%d\n",d[0],d[1]);
	mexPrintf("\nSize:\t%d\n",size);
/*	mexPrintf("\nBuff:\t%d\t%d\t%d\t%d\n",*((double *)buff)[0],*((double *)buff)[1],*((double *)buff)[2],*((double *)buff)[3]);*/
	mxSetData(plhs[1],buff);
	plhs[2] = mxCreateDoubleScalar((double)size);
	return; 
}
