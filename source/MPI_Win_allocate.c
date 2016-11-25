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
	
	if(nrhs!=5) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","5 inputs required.");
	}
	if(nlhs!=2) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}
	/*
	#ifdef DEBUG
	
	MPI_Aint size=*((MPI_Aint *)mxGetData(prhs[0]));
	MPI_Aint size=(MPI_Aint)mxGetScalar(prhs[0]);
	int disp_unit=*((int *)mxGetData(prhs[1]));
	void *baseptr=mxGetData(prhs[4]);
	MPI_Win *win=(MPI_Win *)mxGetData(prhs[5]);
	MPI_Win wwin;
	printf("%d\n",size);
	plhs[0]=mxCreateDoubleScalar((double)MPI_Win_allocate(size,1,MPI_INFO_NULL,MPI_COMM_WORLD,baseptr,&wwin));
	printf("win=%d\n",wwin);
	*((MPI_Win *)mxGetData(prhs[5]))=wwin;
	
	#else
	*/
	mexPrintf("\n Running Allocate \n");
    MPI_Aint size=((MPI_Aint)mxGetScalar(prhs[0]));
    void *baseptr = mxGetData(prhs[4]);
   /*double *baseptr;*/
/*    plhs[2] = mxCreateDoubleScalar(0.0);*/
	mexPrintf("size = %d\n",size);
/*	mexPrintf("\nData in Allocate is = %d\n",mxGetScalar(prhs[4]));*/
	MPI_Win Win;
    plhs[0]=mxCreateDoubleScalar((double)MPI_Win_allocate(size,   /*size*/
                                                          (int)mxGetScalar(prhs[1]),  /*disp_unit*/
                                                          *((MPI_Aint *)mxGetData(prhs[2])), /*info*/
                                                          *((MPI_Comm *)mxGetData(prhs[3])), /*comm*/
                                                          &baseptr,     /* *baseptr*/
                                                          &Win /*win*/
                                                ));
	mexPrintf("\nWin in allocate: %d\n",(double)Win);
/*	mexPrintf("\nbaseptr in allocate: %d\n",*(double *)baseptr);*/
   /* mexMakeMemoryPersistent(baseptr);*/
    plhs[1] = mxCreateDoubleScalar(Win);
    /*plhs[2] = mxCreateDoubleScalar(*baseptr);*/
/*    mexMakeArrayPersistent(plhs[2]);
	mxSetData(plhs[2], baseptr);*/
	mexPrintf("\nPlhs1 in allocate is : %d\n",(MPI_Win)mxGetScalar(plhs[1]));
/*	mexPrintf("\nPlhs2 in allocate is : %d\n",mxGetScalar(plhs[2]));
    #endif*/
	return; 
}
