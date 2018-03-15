all: matrix.o list.o main.o
	gcc -g matrix.o list.o main.o -o main

list.o: list.c
	gcc -g -c list.c

matrix.o: matrix.c
	gcc -g -c matrix.c

main.o : main.c
	gcc -g -c main.c

clean:
	rm *.o

run:
	./main
