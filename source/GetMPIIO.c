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
