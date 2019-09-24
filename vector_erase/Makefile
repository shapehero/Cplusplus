CFLGS = -g -W 
OBJS = vector_erase.o
CC = g++

test : ${OBJS}
	$(CC) ${CFLGS} -o $@ ${OBJS}

.PHONY:clean

clean:
	-rm -f ${OBJS} test
