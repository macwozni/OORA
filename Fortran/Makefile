FORTRAN=gfortran
FLAGS=

SRCDIR=.

OBJS=mm1.o

.PHONY : all
all : tests


tests : $(OBJS)
	$(FORTRAN) $(FLAGS) $^ -o $@

%.o : $(SRCDIR)/%.F90
	$(FORTRAN) $(FLAGS) -c $< -o $@
	


.PHONY : clean
clean :
	rm -f mm1
	rm -f *.mod 
	rm -f *.o
 
