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
	int ii,count=0;
	count=(int)mxGetScalar(prhs[0]);
	MPI_Status status[count];
	if(nrhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","3 inputs required.");
	}
	if(nlhs!=1) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","1 output required.");
	}
	
	plhs[0]=mxCreateDoubleScalar((double)MPI_Waitall(count,     /* count */
												    (MPI_Request *)mxGetData(prhs[1]),
                                                    status      /*status*/
												));

	for (ii=0;ii<count;ii=ii+1)
	{
	*((int *)mxGetData(mxGetField(prhs[2],ii,"count_lo")))=status[ii].count_lo;
	*((int *)mxGetData(mxGetField(prhs[2],ii,"count_hi_and_cancelled")))=status[ii].count_hi_and_cancelled;
	*((int *)mxGetData(mxGetField(prhs[2],ii,"MPI_SOURCE")))=status[ii].MPI_SOURCE;
	*((int *)mxGetData(mxGetField(prhs[2],ii,"MPI_TAG")))=status[ii].MPI_TAG;
	*((int *)mxGetData(mxGetField(prhs[2],ii,"MPI_ERROR")))=status[ii].MPI_ERROR;
	}

	nlhs=1;
	return; 
}
