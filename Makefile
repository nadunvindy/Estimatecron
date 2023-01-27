# A Makefile to build our 'calcmarks' project

C11 = cc -std=c11
CFLAGS = -Wall -Werror
estimatecron : estimatecron.o globals.o simulation.o
	$(C11) $(CFLAGS) -o estimatecron \
estimatecron.o globals.o simulation.o -lm
estimatecron.o : estimatecron.c estimatecron.h
	$(C11) $(CFLAGS) -c estimatecron.c
globals.o : globals.c estimatecron.h
	$(C11) $(CFLAGS) -c globals.c
simulation.o : simulation.c estimatecron.h
	$(C11) $(CFLAGS) -c simulation.c
