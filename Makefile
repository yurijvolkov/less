CC = gcc
OPTS = -g -Wall -pedantic

all : less.o yaio.o loader.o exec.o yastrings.o buffer.o
	$(CC) $(OPTS) -o less less.o yaio.o loader.o exec.o yastrings.o buffer.o  -lcurses

less.o : less.c
	$(CC) $(OPTS) -c less.c 

yaio.o : yaio.c
	$(CC) $(OPTS) -c yaio.c

loader.o : loader.c
	$(CC) $(OPTS) -c loader.c

exec.o : exec.c
	$(CC) $(OPTS) -c exec.c

yastrings.o : yastrings.c
	$(CC) $(OPTS) -c yastrings.c

buffer.o : buffer.c
	$(CC) $(OPTS) -c buffer.c

clean : 
	rm *.o less
