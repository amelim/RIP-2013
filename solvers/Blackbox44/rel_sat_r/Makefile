# CCFLAGS is set up by top level Makefile
CFLAGS = $(CCFLAGS)
ifeq ($(OSTYPE), linux)
  CFLAGS = $(CCFLAGS)
endif
ifeq ($(OSTYPE), cygwin)
  CFLAGS = $(CCFLAGS) -DWIN32
endif
ifeq ($(OSTYPE), posix)
  CFLAGS = $(CCFLAGS)
endif

LINKFLAGS = -s

# ^^^ add -DNDEBUG to turn off assertion checking ^^^

CC = g++

LIBS = -lm

.SUFFIXES: .o .cpp .c

OBJS_c = Random.cpp ClauseList.cpp Clause.cpp SATInstance.cpp sat_solve.cpp LoadCnf.cpp SATSolver.cpp

OBJS_O = $(OBJS_c:.cpp=.o)

#k-sat_solve: $(OBJS_c) $(OBJS_O) SATSolver.c SATSolver.o
#	g++ $(LINKFLAGS) $(CFLAGS) -o rel_sat_r $(OBJS_O) SATSolver.o $(LIBS)


.cpp.o:
	$(CC) $(CFLAGS) -c $< 


all: $(OBJS_O)

clean:
	rm -f *.o rel_sat_r

dist:
	cd .. ;	tar cevof rel_sat_r.tar rel_sat_r ; compress rel_sat_r.tar ; uuencode rel_sat_r.tar.Z rel_sat_r.tar.Z > rel_sat_r.tar.Z.uu ; rm rel_sat_r.tar.Z

install:
	cp rel_sat_r statistics $(HOME)/bin/$(CPUTYPE)

.KEEP_STATE:

