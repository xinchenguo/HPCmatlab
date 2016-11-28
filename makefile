mexcompiler = CC=mpicc CXX=mpicxx 
mexflags = COPTIMFLAGS="-O2 -DNDEBUG" LDOPTIMFLAGS="-O2"

SRC := $(wildcard ./source/*.c)

MEX := $(SRC:%.c=%)

.PHONY: all
all: $(MEX)
	mv *.mex* matlab/;
	cp source/*.m matlab/;

%: %.c
	mex $< $(mexcompiler) $(mexflags);

clean:
	rm -f matlab/*.mex*;
	rm -f *.mex*;
