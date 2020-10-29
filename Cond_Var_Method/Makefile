CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: multi2

multi2: multi2.o email.o
	${CC} multi2.o email.o -o multi2 -pthread

multi2.o: multi2.c
	${CC} ${CFLAGS} multi2.c -pthread

email.o: email.c
	${CC} ${CFLAGS} email.c

clean: 
	rm -f *.o *~

