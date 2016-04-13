CC := gcc
RM := rm -f

sources := tripbrute.c tripgen.c
targets := tripbrute tripgen

.PHONY: clean default all

default: all
all: $(targets)

tripbrute: tripbrute.o
	$(CC) -o tripbrute tripbrute.o
	
tripgen: tripgen.o
	$(CC) -o tripgen tripgen.o
	
tripbrute.o: tripbrute.c
	$(CC) -c -o tripbrute.o tripbrute.c
	
tripgen.o: tripgen.c
	$(CC) -c -o tripgen.o tripgen.c
	
clean:
	$(RM) $(targets) tripgen.o tripbrute.o