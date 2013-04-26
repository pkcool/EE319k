all: main

main: main.o random.o maze.o
	gcc main.o random.o maze.o -o main

main.o: main.c
	gcc -c main.c

random.o: random.c
	gcc -c random.c

maze.o: maze.c
	gcc -c maze.c

clean:
	rm -rf *.o main