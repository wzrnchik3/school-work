# CC = g++
CC = gcc

CFLAGS = -Wall -O2 -I .
LDLIBS = -lpthread

PROGS =	mycloudclient\
	mycloudserver

all: $(PROGS) 
$(PROGS): csapp.o
csapp.o: csapp.c csapp.h

# Programs that need more than one .o file
mycloudserver: mycloudserver.o mycloud.o
 
clean:
	rm -f $(PROGS) *.o *~
