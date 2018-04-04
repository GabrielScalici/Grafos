all: fila.o list.o main.o
	gcc -g fila.o list.o main.o -o main -Wall -std=c99

fila.o:
	gcc -g -c fila.c

list.o:
	gcc -g -c list.c

main.o :
	gcc -g -c main.c

clean:
	rm *.o main

run:
	./main
