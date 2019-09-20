all:my_daemon
CFLAGS=-W -g -std=c++11
CC=g++
OBJ=quick_sort.o

my_daemon:$(OBJ)
	$(CC) $(CFLAGS) -o my_daemon $(OBJ)

quick_sort.o:quick_sort.cpp
	$(CC) $(CFLAGS) -c quick_sort.cpp


.PHONY:clean

clean:
	-rm -f $(OBJ) my_daemon
