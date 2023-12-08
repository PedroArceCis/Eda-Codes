CC=gcc
FLAGS=-Wall

all: TEST clean exe

TEST: main.o funciones.o tda.o
		$(CC) -o $@ $^ $(FLAGS)

main.o: main.c
		$(CC) -c $^ $(FLAGS)

funciones.o: funciones.c
		$(CC) -c $^ $(FLAGS)

tda.o: tda.c
		$(CC) -c $^ $(FLAGS)

main.o: entradas.h
funciones.o: entradas.h
tda.o: entradas.h

clean:
		rm *.o *.gch

exe:

		./TEST $(ARGS)