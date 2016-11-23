/*
 *  This mex function creates and returns the datatype handles
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int MPI_FileSize=0;
	int *pt;
	int N=12;
	MPI_FileSize=sizeof(MPI_File);
	plhs[0]=mxCreateNumericMatrix(1,MPI_FileSize,mxINT8_CLASS,mxREAL);
	if(sizeof(int)==1)
	{
		plhs[1]=mxCreateNumericMatrix(1,N,mxINT8_CLASS,mxREAL);
	}
	else if(sizeof(int)==2)
	{
		plhs[1]=mxCreateNumericMatrix(1,N,mxINT16_CLASS,mxREAL);
	}
	else if(sizeof(int)==4)
	{
		plhs[1]=mxCreateNumericMatrix(1,N,mxINT32_CLASS,mxREAL);
	}
	else if(sizeof(int)==8)
	{
		plhs[1]=mxCreateNumericMatrix(1,N,mxINT64_CLASS,mxREAL);
	}
	nlhs=2;
	pt=(int *)mxGetData(plhs[1]);
	pt[0]=MPI_MODE_RDONLY;
	pt[1]=MPI_MODE_RDWR;
	pt[2]=MPI_MODE_WRONLY;
	pt[3]=MPI_MODE_CREATE;
	pt[4]=MPI_MODE_EXCL;
	pt[5]=MPI_MODE_DELETE_ON_CLOSE;
	pt[6]=MPI_MODE_UNIQUE_OPEN;
	pt[7]=MPI_MODE_APPEND;
	pt[8]=MPI_MODE_SEQUENTIAL;
	
	pt[9]=MPI_SEEK_SET;
	pt[10]=MPI_SEEK_CUR;
	pt[11]=MPI_SEEK_END;
	

    return;
}
