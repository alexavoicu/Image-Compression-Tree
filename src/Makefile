.PHONY: build clean

quadtree: main.o functions.o
	gcc main.o functions.o -o quadtree -Wall

main.o: tree.h
	gcc -c main.c -Wall

functions.o: tree.h
	gcc -c functions.c -Wall
clean:
	rm -f main.o functions.o quadtree