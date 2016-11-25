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
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","6 inputs required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
	}

	 switch(*((MPI_Datatype *)mxGetData(prhs[1])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxDOUBLE_CLASS,mxREAL);
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxSINGLE_CLASS,mxREAL);
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[0]),1,mxINT16_CLASS,mxREAL);
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}
     MPI_Request request;
     plhs[0]=mxCreateDoubleScalar((double)MPI_Irecv(							mxGetData(plhs[1]),  
													(int)mxGetScalar(prhs[0]), 
													*((MPI_Datatype *)mxGetData(prhs[1])), 
													(int)mxGetScalar(prhs[2]),  
													(int)mxGetScalar(prhs[3]), 
													*((MPI_Comm *)mxGetData(prhs[4])),
													 &request
												));
	plhs[2] = mxCreateDoubleScalar((double)request);
	return; 
}
