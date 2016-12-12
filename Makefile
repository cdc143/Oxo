CC=gcc
all: oxo

oxo: main.o game.o
	$(CC) -Wall -o oxo main.o game.o -lcursesw
clean:
	rm *.o oxo
