module load octave/4.0.0
module unload openmpi/1.8.5-gnu-stock
module load mvapich2/2.1-gnu-4.9.2
rm -r octave
mkdir octave
MEXcc=mkoctfile
FLAG="--mex -fPIC -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I/packages/6x/mvapich2/2.1/gcc/4.9.2/normal/include -L/packages/6x/mvapich2/2.1/gcc/4.9.2/normal/lib -lmpicxx -Wl,-rpath -Wl,/packages/6x/mvapich2/2.1/gcc/4.9.2/normal/lib -Wl,--enable-new-dtags -lmpi -lpmi "
rawinc=$(mpicxx -compile_info)
incflag=$(echo $rawinc | sed -e "s/c++/ /g")
#export rawlib=$(mpicc -link_info)
#export libflag=$(echo $rawlib | sed -e "s/gcc/ /g")
Files=./source/*.c
for file in $Files
do
    echo $file
    #$MEXcc $FLAG $incflag $file
    $MEXcc $FLAG $file
done
mv *.mex octave
rm *.o
cp ./source/*.m octave
