all: swordx
swordx: main.o wordList.o sorting.o options.o
	gcc -o swordx main.o wordList.o sorting.o options.o
swordx.o: main.c wordList.c sorting.c options.c
	gcc -c main.c wordList.c sorting.c options.c
clean:
	rm swordx main.o wordList.o sorting.o options.o
