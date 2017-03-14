cd ../..
rm -r octave
mkdir octave
MEXcc=mkoctfile
FLAG="--mex -fPIC -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64"
rawinc=$(mpicc -compile_info)
incflag=$(echo $rawinc | sed -e "s/gcc//")
echo $incflag
Files=./source/*.c
for file in $Files
do
    echo $file
    $MEXcc $FLAG $incflag $file
done
mv *.mex octave
rm *.o
cp ./source/*.m octave
