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
	if(nrhs!=10) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","10 inputs required.");
	}
	if(nlhs!=3) 
	{
		mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","3 output required.");
	}
	
	 switch(*((MPI_Datatype *)mxGetData(prhs[2])))
{
        case MPI_DOUBLE:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxDOUBLE_CLASS,mxREAL);
        break;
        case MPI_FLOAT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxSINGLE_CLASS,mxREAL);
        break;
        case MPI_INT:
        plhs[1] = mxCreateNumericMatrix((int)mxGetScalar(prhs[1]),1,mxINT16_CLASS,mxREAL);
        break;
        default:
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:MPI_DATATYPE","Incompatible Datatype");
}
	 int m =1,n =1;
        int nfields = 5;
        const char *fieldnames[] =                      {                       "count_lo",
                                                                "count_hi_and_cancelled",
                                                                "MPI_SOURCE",
                                                                "MPI_TAG",
                                                                "MPI_ERROR"     };
        plhs[2] = mxCreateStructMatrix(m, n, nfields, fieldnames);

	

	plhs[0]=mxCreateDoubleScalar((double)MPI_Sendrecv(						mxGetData(prhs[0]),  /*sendbuff*/
													(int)mxGetScalar(prhs[1]),  /* count */
													*((MPI_Datatype *)mxGetData(prhs[2])),  /*datatype*/
													(int)mxGetScalar(prhs[3]),  /*dest*/
													(int)mxGetScalar(prhs[4]), /*tag*/
													mxGetData(plhs[1]),  /*recvbuff*/
													(int)mxGetScalar(prhs[5]),  /* count */
													*((MPI_Datatype *)mxGetData(prhs[6])),  /*datatype*/
													(int)mxGetScalar(prhs[7]),  /*source*/
													(int)mxGetScalar(prhs[8]), /*tag*/
													*((MPI_Comm *)mxGetData(prhs[9])), /*comm*/
													&status /*status*/
												));
	mxSetFieldByNumber(plhs[2],0,0,mxCreateDoubleScalar((double)status.count_lo));
        mxSetFieldByNumber(plhs[2],0,1,mxCreateDoubleScalar((double)status.count_hi_and_cancelled));
        mxSetFieldByNumber(plhs[2],0,2,mxCreateDoubleScalar((double)status.MPI_SOURCE));
        mxSetFieldByNumber(plhs[2],0,3,mxCreateDoubleScalar((double)status.MPI_TAG));
        mxSetFieldByNumber(plhs[2],0,4,mxCreateDoubleScalar((double)status.MPI_ERROR));

	return; 
}
