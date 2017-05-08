CC = gcc
OPTS = -Wall -pedantic

all : less.o yaio.o
	$(CC) $(OPTS) -o less less.o yaio.o

less.o : less.c
	$(CC) $(OPTS) -c less.c

yaio.o : yaio.c
	$(CC) $(OPTS) -c yaio.c
