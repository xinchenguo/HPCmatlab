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
