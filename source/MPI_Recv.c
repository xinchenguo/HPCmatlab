/*
    HPCmatlab - Framework for Message Passing in Matlab
    Copyright (C) 2013-2016  Xinchen Guo, Mukul Dave, Ayush Mishra & Mohamed Sayeed

    This file is part of HPCmatlab.

    HPCmatlab is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    HPCmatlab is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA

    Email IDs: xinchen.guo@asu.edu, mukul92@gmail.com,
               ayush02mishra@gmail.com, msayeed@asu.edu
*/

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int size;
	MPI_Status status;
	if(nrhs!=7) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","7 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_Recv(	mxGetData(prhs[0]),  /*buff*/
													(int)mxGetScalar(prhs[1]),  /* count */
													*((MPI_Datatype *)mxGetData(prhs[2])),  /*datatype*/
													(int)mxGetScalar(prhs[3]),  /*source*/
													(int)mxGetScalar(prhs[4]), /*tag*/
													*((MPI_Comm *)mxGetData(prhs[5])), /*comm*/
													&status /*status*/
												));
/*
	*((int *)mxGetData(mxGetField(prhs[6],0,"count_lo")))=status.count_lo;
	*((int *)mxGetData(mxGetField(prhs[6],0,"count_hi_and_cancelled")))=status.count_hi_and_cancelled;
	*((int *)mxGetData(mxGetField(prhs[6],0,"MPI_SOURCE")))=status.MPI_SOURCE;
	*((int *)mxGetData(mxGetField(prhs[6],0,"MPI_TAG")))=status.MPI_TAG;
	*((int *)mxGetData(mxGetField(prhs[6],0,"MPI_ERROR")))=status.MPI_ERROR;
*/
	nlhs=1;
	return; 
}
