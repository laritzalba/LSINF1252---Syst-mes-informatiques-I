CC = gcc
OPT = -g -Wall -W -Werror -std=gnu99

all : .PHONY test

test : matrix.o test.o
	$(CC) $(OPT) matrix.o test.o -lcunit -o test

test.o : test.o matrix.h
	$(CC) $(OPT) -lcunit -c test.c
	
.PHONY : clean 

clean :
	rm -f *.o test
