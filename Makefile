all: exec


gen.o: gen.c header.h
	gcc -c gen.c -o gen.o

main.o: main.c header.h
	gcc -c main.c -o main.o

exec: gen.o main.o
	gcc gen.o main.o -o exec

clean:
	rm -f *.o
	rm exec
