# Makefile for OPS exercise 2
# Use tabs for indentation, not spaces!

all: printversion getsignal sendsignal

# Link object files and create a binary executable:
getsignal:
	gcc -Wall getsignal.c -o getsignal

sendsignal:
	gcc -Wall sendsignal.c -o sendsignal

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
clean:
	rm -f *.o

cleanall: clean
	rm -f getsignal sendsignal

printversion:
	gcc --version | grep gcc
