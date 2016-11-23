module load mvapich2/2.1-gnu-4.9.2
module load matlab/2016a
rm -r -f matlab
mkdir matlab
Files=./source/*.c
mexcompiler="CC=mpicc CXX=mpicxx "
for file in $Files
do
    echo $file
    mex $file $mexcompiler COPTIMFLAGS="-O2 -DNDEBUG" LDOPTIMFLAGS="-O2"
done
mv *.mexa64 matlab
cp ./source/*.m matlab
##chgrp A2C2dev matlab
