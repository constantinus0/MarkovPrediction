# Sample makefile for small/medium projects

# dirs for included files
IDIR =.
# define compiler
CC=gcc
# define additional flags for the compilation process, e.g. -I. -Lpath
CFLAGS=-I$(IDIR)
# dir for object files 
ODIR=obj
# dir for additional libraries (external)
# LDIR =../lib
# external library names
# LIBS=-lm

# dependencies (header files)
_DEPS = functions.h
# patsubst: pattern substitute
# $(patsubst pattern,replacement,text) #'%' works as '*' wildcard
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# this just prepends the IDIR before the _DEPS string

# object files
_OBJ = readFile.o diff.o minmax.o baseVector.o stateId.o stateMatrix.o smooth1d.o transitionMatrix.o probabilityMatrix.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# rule: all "*.o" depend on "*.c" and the "DEPS" and should be compiled as displayed below 
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

# rule: 
test.exe: test.c $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

# specifies that the "clean" rule does not depend on specific files, so that the makefile will not try to re-run it when things change. Also useful in "all" rules. 
.PHONY: clean

# remove all "*.o" files in the "ODIR" directory, as well as all temp files (marked with an '~' character). To be executed by calling "make clean".
clean:
	rm -f $(ODIR)/*.o *~ *.exe core $(INCDIR)/*~ ./*.o

