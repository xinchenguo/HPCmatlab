%%    HPCmatlab - Framework for Message Passing in Matlab
%%    Copyright (C) 2013-2016  Xinchen Guo, Mukul Dave, Ayush Mishra & Mohamed Sayeed
%%
%%    This file is part of HPCmatlab.
%%
%%    HPCmatlab is free software; you can redistribute it and/or
%%    modify it under the terms of the GNU Lesser General Public
%%    License as published by the Free Software Foundation; either
%%    version 2.1 of the License, or (at your option) any later version.
%%
%%    HPCmatlab is distributed in the hope that it will be useful,
%%    but WITHOUT ANY WARRANTY; without even the implied warranty of
%%    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
%%    Lesser General Public License for more details.
%%
%%    You should have received a copy of the GNU Lesser General Public
%%    License along with this library; if not, write to the Free Software
%%    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
%%    USA
%%
%%    Email IDs: xinchen.guo@asu.edu, mukul92@gmail.com,
%%               ayush02mishra@gmail.com, msayeed@asu.edu
%%

% Get the communicator MPI_COMM_WORLD
MPI_COMM_WORLD=GetMPICOMMWORLD;

% Get MPI Datatype handles
MPIDataTypeArray=GetMPIDataType;
MPI_CHAR=MPIDataTypeArray(1);
MPI_SIGNED_CHAR=MPIDataTypeArray(2);
MPI_UNSIGNED_CHAR=MPIDataTypeArray(3);
MPI_BYTE=MPIDataTypeArray(4);
MPI_WCHAR=MPIDataTypeArray(5);
MPI_SHORT=MPIDataTypeArray(6);
MPI_UNSIGNED_SHORT=MPIDataTypeArray(7);
MPI_INT=MPIDataTypeArray(8);
MPI_UNSIGNED=MPIDataTypeArray(9);
MPI_LONG=MPIDataTypeArray(10);
MPI_UNSIGNED_LONG=MPIDataTypeArray(11);
MPI_FLOAT=MPIDataTypeArray(12);
MPI_DOUBLE=MPIDataTypeArray(13);
MPI_LONG_DOUBLE=MPIDataTypeArray(14);
MPI_LONG_LONG_INT=MPIDataTypeArray(15);
MPI_UNSIGNED_LONG_LONG=MPIDataTypeArray(16);
MPI_LONG_LONG=MPIDataTypeArray(17);
clear MPIDataTypeArray

% Get the operation handles
MPIOpArray=GetMPIOp;
MPI_MAX=MPIOpArray(1);
MPI_MIN=MPIOpArray(2);
MPI_SUM=MPIOpArray(3);
MPI_PROD=MPIOpArray(4);
MPI_LAND=MPIOpArray(5);
MPI_BAND=MPIOpArray(6);
MPI_LOR=MPIOpArray(7);
MPI_BOR=MPIOpArray(8);
MPI_LXOR=MPIOpArray(9);
MPI_BXOR=MPIOpArray(10);
MPI_MINLOC=MPIOpArray(11);
MPI_MAXLOC=MPIOpArray(12);
MPI_REPLACE=MPIOpArray(13);
MPI_NO_OP=MPIOpArray(14);
clear MPIOpArray


[MPI_Count,C_INT,MPI_Request,MPI_Win,MPI_Datatype,MPI_Aint,MPI_Info,MPI_Offset]=GetMPITYPES;

%MPI_INFO_NULL=hex2dec('1c000000')*ones(1,1,'like',MPI_Info);
%MPI_LOCK_SHARED=235*ones(1,1,'like',C_INT);
%MPI_LOCK_EXCLUSIVE=234*ones(1,1,'like',C_INT);
MPI_INFO_NULL=hex2dec('1c000000')*ones(1,1,'int32');
MPI_LOCK_SHARED=235*ones(1,1,'int32');
MPI_LOCK_EXCLUSIVE=234*ones(1,1,'int32');

% Creating the MPI_Status struct
% Updated according to the definition in "/packages/mvapich2/2.0.1/gcc/stock/normal/include/mpi.h"
f1='count_lo';
v1=C_INT;
f2='count_hi_and_cancelled';
v2=C_INT;
f3='MPI_SOURCE';
v3=C_INT;
f4='MPI_TAG';
v4=C_INT;
f5='MPI_ERROR';
v5=C_INT;
MPI_Status=struct(f1,v1,f2,v2,f3,v3,f4,v4,f5,v5);
clear f1 v1 f2 v2 f3 v3 f4 v4 f5 v5

[MPI_File,MPIIOArray]=GetMPIIO;
MPI_MODE_RDONLY=MPIIOArray(1);
MPI_MODE_RDWR=MPIIOArray(2);
MPI_MODE_WRONLY=MPIIOArray(3);
MPI_MODE_CREATE=MPIIOArray(4);
MPI_MODE_EXCL=MPIIOArray(5);
MPI_MODE_DELETE_ON_CLOSE=MPIIOArray(6);
MPI_MODE_UNIQUE_OPEN=MPIIOArray(7);
MPI_MODE_APPEND=MPIIOArray(8);
MPI_MODE_SEQUENTIAL=MPIIOArray(9);
	
MPI_SEEK_SET=MPIIOArray(10);
MPI_SEEK_CUR=MPIIOArray(11);
MPI_SEEK_END=MPIIOArray(12);
clear MPIIOArray





