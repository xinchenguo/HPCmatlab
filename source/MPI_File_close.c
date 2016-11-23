
#include "mex.h"
#include "mpi.h"
#include <string.h>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	MPI_File fh;
	
	if(nrhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","1 input required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	memcpy(&fh,mxGetData(prhs[0]),sizeof(MPI_File));
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_File_close(
								                        &fh /*MPI_File*/
								                    ));

    memcpy(mxGetData(prhs[0]),&fh,sizeof(MPI_File));

	nlhs=1;
	return; 
}
