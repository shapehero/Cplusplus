all:my_daemon
CFLAGS=-W -g -std=c++11
CC=g++
OBJ=get_loop_array_index.o

my_daemon:$(OBJ)
	$(CC) $(CFLAGS) -o my_daemon $(OBJ)

get_loop_array_index.o:get_loop_array_index.cpp
	$(CC) $(CFLAGS) -c get_loop_array_index.cpp


.PHONY:clean

clean:
	-rm -f $(OBJ) my_daemon
