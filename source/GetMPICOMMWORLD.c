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
 *  This mex function returns the communicator MPI_COMM_WORLD
 */

#include "mex.h"
#include "mpi.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int MPI_CommSize=0;
	
	MPI_CommSize=sizeof(MPI_Comm);
	if(sizeof(MPI_Comm)==1)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT8_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==2)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT16_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==4)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	else if(sizeof(MPI_Comm)==8)
	{
		plhs[0]=mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
		*((MPI_Comm *)mxGetData(plhs[0]))=MPI_COMM_WORLD;
	}
	nlhs=1;		

	return;
}
