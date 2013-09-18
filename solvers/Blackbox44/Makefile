# General CC flags exported to sub-Makefiles
# Note: nonnull-objects no longer supported
# CCFLAGS = -g -fconserve-space -Wall
# CCFLAGS = -g -Wall
# CCFLAGS = -Wall  -DNDEBUG -O1
# Use -m32 to allow ints to hold pointers
CCFLAGS = -Wall  -DNDEBUG -O1 -m32
# CCFLAGS = -O3 -fconserve-space -Wall -DNDEBUG
export CCFLAGS

# Link flags
# try -lfl if -ll doesn't work
LFLAGS = -ll
ifeq ($(OSTYPE), linux)
  LFLAGS = -lfl
endif
ifeq ($(OSTYPE), cygwin)
# dec 2001 - looks like cygwin has neither -lfl nor -ll, but 
# neither are necessary
  LFLAGS =
endif
ifeq ($(OSTYPE), posix)
  LFLAGS = -lfl
endif

LFLAGS = -lfl

# Special defined variables
DFLAGS =
ifeq ($(OSTYPE), cygwin)
  DFLAGS = -DUSENAMESPACESTD
endif
export DFLAGS

# Turn on or off code for control, learning, variable ordering
#BBFLAGS = -DBBCTRL
#BBFLAGS = -DBBLEARN
#BBFLAGS = -DBBVARORDER

#CC = gcc -g2 -Wall -O2
#CC = gcc -g2
CC = g++ $(BBFLAGS) $(DFLAGS) $(CCFLAGS)
V = 43

.SUFFIXES: .o .cpp .c

OBJS = bbpddl.tab.o lex.yy.o graphplan.o utilities.o hash.o planner.o dummy.o graph2wff.o control.o justify.o tim.o learn.o verify.o bbio.o sat_solver.o

blackbox: $(OBJS)
	cd compact; make
	cd satz-rand; make
	cd walksat; make
	cd rel_sat_r; make
	cd zchaff; make
	$(CC) compact/*.o satz-rand/*.o walksat/*.o rel_sat_r/*.o $(OBJS) $(LFLAGS) zchaff/libsat.a -lm -o $@ 

simpleblackbox: $(OBJS)
	$(CC) $(OBJS) -ll -o blackbox

#graphplan: y.tab.o lex.yy.o graphplan.o utilities.o hash.o planner.o dummy.o
#	$(CC) lex.yy.o y.tab.o hash.o utilities.o graphplan.o planner.o dummy.o -o graphplan

all:
	make clean; make; make install; make clean

y.tab.o: y.tab.h graphplan.h 

graph2wff.o: graphplan.h interface.h

hash.o: graphplan.h

graphplan.o: graphplan.h interface.h graphplan.cpp
	$(CC) -c -DVERSION=\"$(V)\" graphplan.cpp

utilities.o: graphplan.h

planner.o: graphplan.h interface.h

justify.o: justify.h graphplan.h

tim.o: tim.h graphplan.h

learn.o: tim.h learn.h graphplan.h

bbio.o: learn.h graphplan.h

verify.o: verify.h learn.h graphplan.h

sat_solver.o: sat_solver.cpp
	$(CC) -c sat_solver.cpp

# Bison and flex not installed - should be okay to use old .tab.cpp file
#
#lex.yy.cpp: bbpddl.l
#	flex -olex.yy.cpp bbpddl.l 
#
# bbpddl.tab.cpp: bbpddl.y lex.yy.cpp
#	bison -d bbpddl.y -o bbpddl.tab.cpp

lex.yy.o: graphplan.h bbpddl.tab.cpp.h control.h lex.yy.cpp

bbpddl.tab.o: graphplan.h control.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< 

install: blackbox
	cp blackbox $(HOME)/bin/`cputype`/blackbox
	cp extract $(HOME)/bin/`cputype`
	cp Run-bb $(HOME)/bin/`cputype`

clean:
	rm -f *.o blackbox
	cd satz-rand; make clean
	cd walksat; make clean
	cd compact; make clean
	cd rel_sat_r; make clean
	cd zchaff; make clean

dist:
	D=`pwd`; cd ..; rm -f blackbox*.tar*; tar cvof blackbox$(V).tar $${D##*/}; compress blackbox$(V).tar; uuencode blackbox$(V).tar.Z blackbox$(V).tar.Z > blackbox$(V)_tar_Z.uu ; rm blackbox$(V).tar.Z

everything:
	make clean; make; make install; make clean; cleanup; make dist

