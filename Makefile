CFLAGS = -Wall

all: smidi.o

example: example.o smidi.o

example.o: smidi.h

smidi.o: smidi.c smidi.h

clean:
	-rm -f smidi.o example example.o
