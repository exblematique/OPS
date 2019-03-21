# Makefile for OPS exercise 2
# Use tabs for indentation, not spaces!

all: printversion display

# Link object files and create a binary executable:
display: display.o displayFunctions.o syntaxCheck.o
	gcc -Wall -o display display.o displayFunctions.o syntaxCheck.o

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
display.o: display.c displayFunctions.h errorCodes.h
	gcc -c -Wall display.c

displayFunctions.o: displayFunctions.c displayFunctions.h syntaxCheck.h errorCodes.h
	gcc -c -Wall displayFunctions.c

syntaxCheck.o: syntaxCheck.c syntaxCheck.h errorCodes.h
	gcc -c -Wall syntaxCheck.c

clean:
	rm -f *.o

cleanall: clean
	rm -f display

printversion:
	gcc --version | grep gcc
