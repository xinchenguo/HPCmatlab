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
	int ii,count=0;
        count=(int)mxGetScalar(prhs[0]);
        MPI_Status status[count];
	double *r = mxGetPr(prhs[1]);
	if(nrhs!=2)
        {
                mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","2 inputs required.");
        }
        if(nlhs!=2)
        {
                mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","2 output required.");
        }
        int m =count,n =1;
        int nfields = 5;
        const char *fieldnames[] =                      {                       "count_lo",
                                                                "count_hi_and_cancelled",
                                                                "MPI_SOURCE",
                                                                "MPI_TAG",
                                                                "MPI_ERROR"     };
        plhs[1] = mxCreateStructMatrix(m, n, nfields, fieldnames);
        MPI_Request request[count];
	for (ii=0;ii<count;ii=ii+1)
        {
	request[ii] = r[ii];
	
	}

        /*mexPrintf("Running Waitall with Request: \n %d and %d\n",request[0],request[1]);*/

        plhs[0]=mxCreateDoubleScalar((double)MPI_Waitall(					count,     /* count */
                                                                                                request,
                                                    						status      /*status*/
                                                                                                					));

      	/*mexPrintf("\nstatus1: %d     status2: %d\n",status[0].MPI_TAG,status[1].MPI_TAG);*/
	for (ii=0;ii<count;ii=ii+1)
	{
	mxSetFieldByNumber(plhs[1],ii,0,mxCreateDoubleScalar((double)status[ii].count_lo));
	mxSetFieldByNumber(plhs[1],ii,1,mxCreateDoubleScalar((double)status[ii].count_hi_and_cancelled));
	mxSetFieldByNumber(plhs[1],ii,2,mxCreateDoubleScalar((double)status[ii].MPI_SOURCE));
	mxSetFieldByNumber(plhs[1],ii,3,mxCreateDoubleScalar((double)status[ii].MPI_TAG));
	mxSetFieldByNumber(plhs[1],ii,4,mxCreateDoubleScalar((double)status[ii].MPI_ERROR));
	}

	return; 
}
