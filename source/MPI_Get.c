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
/*	double *w = mxGetPr(prhs[7]);*/
        MPI_Win win = mxGetScalar(prhs[7]);
	if(nrhs!=8) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","8 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
    mexPrintf("\nWin in Get : %d", win /*win*/);	
	mexPrintf("\nData in get :%d\n",mxGetScalar(prhs[0]));
    plhs[0]=mxCreateDoubleScalar((double)MPI_Get(	mxGetData(prhs[0]),  /*origin_addr*/
													(int)mxGetScalar(prhs[1]),  /*origin_count */
													*((MPI_Datatype *)mxGetData(prhs[2])),  /*origin_datatype*/
													(int)mxGetScalar(prhs[3]),  /*target_rank*/
													*((MPI_Aint *)mxGetData(prhs[4])), /*target_disp*/
													(int)mxGetScalar(prhs[5]),  /*target_count*/
													*((MPI_Datatype *)mxGetData(prhs[6])),  /*target_datatype*/
													win /*win*/
												));
	mexPrintf("\nData in get :%d\n",mxGetScalar(prhs[0]));
	return; 
}
