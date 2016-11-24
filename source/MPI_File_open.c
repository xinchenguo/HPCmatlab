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
