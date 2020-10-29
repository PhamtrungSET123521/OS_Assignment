CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: multi

multi: multi.o email.o
	${CC} multi.o email.o -o multi -pthread

multi.o: multi.c
	${CC} ${CFLAGS} multi.c -pthread

email.o: email.c
	${CC} ${CFLAGS} email.c

clean: 
	rm -f *.o *~


