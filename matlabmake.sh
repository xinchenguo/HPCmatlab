module load mvapich2
module load matlab/R2014a
rm -r -f matlab
mkdir matlab
Files=./source/*.c
mexcompiler="CC=mpicc CXX=mpicxx "
for file in $Files
do
    echo $file
    mex $file $mexcompiler COPTIMFLAGS="-O2 -DNDEBUG" LDOPTIMFLAGS="-O2"
done
mv *.mex* matlab
cp ./source/*.m matlab
