CFLAGS = -Wall

all: smidi.o

example: example.o smidi.o

smidi.o: smidi.c smidi.h

clean:
	-rm -f smidi.o example example.o
