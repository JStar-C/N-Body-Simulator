# Authors: Joseph Calles and Tharith Sovann

CC = g++
CFLAGS = -O3 -g -Wall -Werror -std=c++14 -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJECTS = main.o Body.o

all: NBody

NBody: main.o Body.o
	$(CC) $(CFLAGS) -o NBody main.o Body.o $(LIBS)

main.o: main.cpp Body.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

Body.o: Body.cpp Body.hpp
	$(CC) $(CFLAGS) -c Body.cpp -o Body.o

clean:
	\rm NBody *~ *.o 
