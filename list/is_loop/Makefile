all:my_daemon
CFLAGS=-W -g -std=c++11
CC=g++
OBJ=is_loop.o

my_daemon:$(OBJ)
	$(CC) $(CFLAGS) -o my_daemon $(OBJ)

is_loop.o:is_loop.cpp
	$(CC) $(CFLAGS) -c is_loop.cpp


.PHONY:clean

clean:
	-rm -f $(OBJ) my_daemon
