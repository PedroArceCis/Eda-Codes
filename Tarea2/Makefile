CC=gcc
FLAGS=-lm

all: TEST clean exe

TEST: main.o funciones.o sorting.o
		$(CC) -o $@ $^ $(FLAGS)

main.o: main.c
		$(CC) -c $^ $(FLAGS)

funciones.o: funciones.c
		$(CC) -c $^ $(FLAGS)

sorting.o: sorting.c
		$(CC) -c $^ $(FLAGS)

main.o: tweets.h
funciones.o: tweets.h
sorting.o: tweets.h

clean:
		rm *.o *.gch

exe:

		./TEST $(ARGS)