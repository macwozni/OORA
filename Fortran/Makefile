FORTRAN=gfortran
CC=gcc
FFLAGS=
CFLAGS=
COMMONFLAGS=

SRCDIR=.

FOBJS=fmm1.o
COBJS=cmm1.o

.PHONY : all
all : ftests ctests


ftests : $(FOBJS)
	$(FORTRAN) $(FFLAGS) $(COMMONFLAGS) $^ -o $@

%.o : $(SRCDIR)/%.F90
	$(FORTRAN) $(FFLAGS) $(COMMONFLAGS) -c $< -o $@
	

ctests : $(COBJS)
	$(CC) $(CFLAGS) $(COMMONFLAGS) $^ -o $@

%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(COMMONFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -f ftests
	rm -f *.mod 
	rm -f *.o
	rm -f ctests
	
 
