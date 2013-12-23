CC=gcc
INCLUDES=-I./SystemAPI
OBJECTS=SystemCalls.o gateeMenu.o
OUTPUT=gatee
FLAGS=-lmenu -lncurses

gatee: $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS) $(FLAGS) $(INCLUDES)
	@echo 'First type "export PATH=$$PATH:$$(pwd)"'
	@echo 'Then run Gatee using ". runGatee"'

gateeMenu.o: gateeMenu.c gateeMenu.h
	$(CC) -c gateeMenu.c gateeMenu.h

SystemCalls.o: SystemAPI/SystemCalls.c SystemAPI/SystemCalls.h
	$(CC) -c SystemAPI/SystemCalls.c $(INCLUDES)

test: systemCallTest.o SystemCalls.o
	$(CC) -o test systemCallTest.o SystemCalls.o $(INCLUDES)

systemCallTest.o: systemCallTest.c
	$(CC) -c systemCallTest.c

clean:
	rm -f gatee test *.o ./SystemAPI/*.o *.out *.gch