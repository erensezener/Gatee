CC=gcc

OBJECTS=SystemCalls.o gateeMenu.o
OUTPUT=gatee
FLAGS=-lmenu -lncurses

gatee: $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS) $(FLAGS)
	@echo 'First type "export PATH=$$PATH:$$(pwd)"'
	@echo 'Then run Gatee using ". runGatee"'

gateeMenu.o: gateeMenu.c gateeMenu.h
	$(CC) -c gateeMenu.c gateeMenu.h $(FLAGS)

SystemCalls.o: SystemCalls.c SystemCalls.h
	$(CC) -c SystemCalls.c

test: systemCallTest.o SystemCalls.o
	$(CC) -o test systemCallTest.o SystemCalls.o

systemCallTest.o: systemCallTest.c
	$(CC) -c systemCallTest.c

clean:
	rm -f gatee test *.o *.out *.gch
