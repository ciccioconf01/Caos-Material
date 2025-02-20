all: program.elf

program.elf : main.o utils.o
	gcc -pie main.o utils.o -o program.elf

main.o : main.c
	gcc -c main.c -o main.o

utils.o : utils.c
	gcc -c utils.c -o utils.o

clean:
	rm *.o
	rm *.elf
	rm *.out