all: heap.o matrix.o main.o 
	gcc -g heap.o matrix.o main.o -o main -Wall -std=c99

heap.o:
	gcc -g -c heap.c

matrix.o:
	gcc -g -c matrix.c

main.o :
	gcc -g -c main.c

clean:
	rm *.o main

run:
	./main
 
