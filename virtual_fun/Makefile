all:my_daemon
CFLAGS=-W -g -std=c++11
CC=g++
OBJ=animal.o

my_daemon:$(OBJ)
	$(CC) $(CFLAGS) -o my_daemon $(OBJ)

animal.o:animal.cpp
	$(CC) $(CFLAGS) -c animal.cpp


.PHONY:clean

clean:
	-rm -f $(OBJ) my_daemon
