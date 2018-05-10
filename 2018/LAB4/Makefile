all: matrix.o main.o 
	gcc -g matrix.o main.o -o main -Wall -std=c99

matrix.o:
	gcc -g -c matrix.c

main.o :
	gcc -g -c main.c

clean:
	rm *.o main

run:
	./main
 
