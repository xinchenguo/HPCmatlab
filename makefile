SRC:=$(wildcard ./source/*.c)
all: $(SRC)
	for file in $? ; do \
	mex $$file CC=mpicc CXX=mpicxx COPTIMFLAGS="-O2 -DNDEBUG" LDOPTIMFLAGS="-O2"; \
	done
	cp *.mex* matlab/;
	touch all;
clear:
	rm -f matlab/*.mex*;
