/*
 *  This mex function creates and returns the Operator handles to be used in HPCmatlab
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int MPI_CommSize=0,size=14;
	MPI_Op *pt;
	MPI_CommSize=sizeof(MPI_Op);
	if(sizeof(MPI_Comm)==1)
	{
		plhs[0]=mxCreateNumericMatrix(1,size,mxINT8_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==2)
	{
		plhs[0]=mxCreateNumericMatrix(1,size,mxINT16_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==4)
	{
		plhs[0]=mxCreateNumericMatrix(1,size,mxINT32_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==8)
	{
		plhs[0]=mxCreateNumericMatrix(1,size,mxINT64_CLASS,mxREAL);
	}
	nlhs=1;
	pt=(MPI_Op *)mxGetData(plhs[0]);
	pt[0]=MPI_MAX;
	pt[1]=MPI_MIN;
	pt[2]=MPI_SUM;
	pt[3]=MPI_PROD;
	pt[4]=MPI_LAND;
	pt[5]=MPI_BAND;
	pt[6]=MPI_LOR;
	pt[7]=MPI_BOR;
	pt[8]=MPI_LXOR;
	pt[9]=MPI_BXOR;
	pt[10]=MPI_MINLOC;
	pt[11]=MPI_MAXLOC;
	pt[12]=MPI_REPLACE;
	pt[13]=MPI_NO_OP;

	return;
}
