CC=gcc
INCLUDES=-I./SystemAPI
OBJECTS=SystemCalls.o gateeMenu.o
OUTPUT=gatee
FLAGS=-lmenu -lncurses

gatee: $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS) $(FLAGS) $(INCLUDES)
	echo "Compiled & linked."

gateeMenu.o: gateeMenu.c
	$(CC) -c gateeMenu.c

SystemCalls.o: SystemCalls.c SystemCalls.h
	$(CC) -c SystemCalls.c

clean:
	rm -f *.app *.o *.out
