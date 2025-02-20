# Makefile for multi-file program
COMP = gcc
FLAGS = -Wall

all: program.elf

program.elf: main.o utils.o
	$(COMP) -pie main.o utils.o -o progma.elf

main.o: main.c
	$(COMP) -c $(FLAGS) main.c -o main.o

utils.o: utils.c
	$(COMP) -c $(FLAGS) utils.c -o utils.o

clean:
	rm -f *.elf
	rm -f *.o