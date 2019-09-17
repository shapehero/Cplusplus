all:my_daemon
CFLAGS=-W -g -std=c++11 -pthread
CC=g++
OBJ=producer_consumer.o

my_daemon:$(OBJ)
	$(CC) $(CFLAGS) -o my_daemon $(OBJ)

producer_consumer.o:producer_consumer.cpp
	$(CC) $(CFLAGS) -c producer_consumer.cpp


.PHONY:clean

clean:
	-rm -f $(OBJ) my_daemon
