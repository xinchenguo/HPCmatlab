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

/*
 *  This mex function allocates and returns special MPI type handles
 */

#include "mex.h"
#include "mpi.h"
#define N 8
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int Size[N],ii;
	Size[0]=sizeof(MPI_Count);
	Size[1]=sizeof(int);
	Size[2]=sizeof(MPI_Request);
    Size[3]=sizeof(MPI_Win);
    Size[4]=sizeof(MPI_Datatype);
    Size[5]=sizeof(MPI_Aint);
    Size[6]=sizeof(MPI_Info);
    Size[7]=sizeof(MPI_Offset);
	for(ii=0;ii<N;ii++)
	{
		if(Size[ii]==1)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT8_CLASS,mxREAL);
			*((int8_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==2)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT16_CLASS,mxREAL);
			*((int16_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==4)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
			*((int32_T *)mxGetData(plhs[ii]))=0;
		}
		else if(Size[ii]==8)
		{
			plhs[ii]=mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
			*((int64_T *)mxGetData(plhs[ii]))=0;
		}
	}
	nlhs=N;		
	

	return;
}
