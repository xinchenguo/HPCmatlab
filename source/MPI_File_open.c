
#include "mex.h"
#include "mpi.h"
#include <string.h>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	char *filename;
	MPI_File fh;
	
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","5 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	
	filename=mxArrayToString(prhs[1]);
	
	if(filename==NULL)
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","Error File Name");
	}
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_File_open(
													*((MPI_Comm *)mxGetData(prhs[0])), /*comm*/
												    filename, /*file name*/
												    (int)mxGetScalar(prhs[2]),  /* mode */
												    *((MPI_Aint *)mxGetData(prhs[3])), /*info*/
													&fh /*MPI_File*/
												    ));
	memcpy(mxGetData(prhs[4]),&fh,sizeof(MPI_File));
	nlhs=1;
	mxFree(filename);
	return; 
}
