# A Makefile to build our 'calcmarks' project
estimatecron : estimatecron.o globals.o simulation.o
	cc -std=c11 -Wall -Werror -o estimatecron \
estimatecron.o globals.o simulation.o -lm
estimatecron.o : estimatecron.c estimatecron.h
	cc -std=c11 -Wall -Werror -c estimatecron.c
globals.o : globals.c estimatecron.h
	cc -std=c11 -Wall -Werror -c globals.c
simulation.o : simulation.c estimatecron.h
	cc -std=c11 -Wall -Werror -c simulation.c
