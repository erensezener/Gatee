CC=gcc
INCLUDES=-I./SystemAPI
OBJECTS=SystemCalls.o gateeMenu.o
OUTPUT=gatee
FLAGS=-lmenu -lncurses

gatee: $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS) $(FLAGS) $(INCLUDES)
	rm -f *.o *.out *.gch
	echo "Compiled & linked."

gateeMenu.o: gateeMenu.c gateeMenu.h
	$(CC) -c gateeMenu.c gateeMenu.h

SystemCalls.o: SystemAPI/SystemCalls.c SystemAPI/SystemCalls.h
	$(CC) -c SystemAPI/SystemCalls.c $(INCLUDES)

clean:
	rm -f gatee *.o *.out *.gch
