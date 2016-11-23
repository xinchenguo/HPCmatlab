/*
 *  This mex function creates and returns the datatype handles
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int MPI_CommSize=0;
	MPI_Datatype *pt;
	MPI_CommSize=sizeof(MPI_Datatype);
	if(sizeof(MPI_Comm)==1)
	{
		plhs[0]=mxCreateNumericMatrix(1,17,mxINT8_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==2)
	{
		plhs[0]=mxCreateNumericMatrix(1,17,mxINT16_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==4)
	{
		plhs[0]=mxCreateNumericMatrix(1,17,mxINT32_CLASS,mxREAL);
	}
	else if(sizeof(MPI_Comm)==8)
	{
		plhs[0]=mxCreateNumericMatrix(1,17,mxINT64_CLASS,mxREAL);
	}
	nlhs=1;
	pt=(MPI_Datatype *)mxGetData(plhs[0]);
	pt[0]=MPI_CHAR;
	pt[1]=MPI_SIGNED_CHAR;
	pt[2]=MPI_UNSIGNED_CHAR;
	pt[3]=MPI_BYTE;
	pt[4]=MPI_WCHAR;
	pt[5]=MPI_SHORT;
	pt[6]=MPI_UNSIGNED_SHORT;
	pt[7]=MPI_INT;
	pt[8]=MPI_UNSIGNED;
	pt[9]=MPI_LONG;
	pt[10]=MPI_UNSIGNED_LONG;
	pt[11]=MPI_FLOAT;
	pt[12]=MPI_DOUBLE;
	pt[13]=MPI_LONG_DOUBLE;
	pt[14]=MPI_LONG_LONG_INT;
	pt[15]=MPI_UNSIGNED_LONG_LONG;
	pt[16]=MPI_LONG_LONG;

    return;
}
