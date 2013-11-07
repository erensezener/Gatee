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

SystemCalls.o: SystemAPI/SystemCalls.c SystemAPI/SystemCalls.h
	$(CC) -c SystemAPI/SystemCalls.c $(INCLUDES)

clean:
	rm -f gatee *.o *.out
