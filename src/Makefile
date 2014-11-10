

COMPILER = g++
COMPILER_OPTS = -c -g -Wall

LINKER = g++
LINKER_OPTS = -o bdd

OBJS = cnf.o test.o bdd.o

all : $(OBJS)
	$(LINKER) $(LINKER_OPTS) $(OBJS)

cnf.o : cnf.h cnf.cpp
	$(COMPILER) $(COMPILER_OPTS) cnf.cpp

test.o : test.cpp cnf.h
	$(COMPILER) $(COMPILER_OPTS) test.cpp

bdd.o : bdd.h bdd.cpp
	$(COMPILER) $(COMPILER_OPTS) bdd.cpp

.PHONY: help

help:
	@echo "The following make targets are supported:";\
	echo " clean - clean compilation files";\
	echo " help - show this information";\

clean:
	rm -rf *~ *.o bdd
