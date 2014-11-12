

COMPILER = g++
COMPILER_OPTS = -c -g -Wall

LINKER = g++
LINKER_OPTS = -o bdd

OBJS = cnf.o bdd.o test.o

all : $(OBJS)
	$(LINKER) $(LINKER_OPTS) $(OBJS)

cnf.o : cnf.h cnf.cpp
	$(COMPILER) $(COMPILER_OPTS) cnf.cpp

bdd.o : bdd.h bdd.cpp
	$(COMPILER) $(COMPILER_OPTS) bdd.cpp

test.o : cnf.h bdd.h test.cpp
	$(COMPILER) $(COMPILER_OPTS) test.cpp

.PHONY: help

help:
	@echo "The following make targets are supported:";\
	echo " clean - clean compilation files";\
	echo " help - show this information";\

clean:
	rm -rf *~ *.o bdd
