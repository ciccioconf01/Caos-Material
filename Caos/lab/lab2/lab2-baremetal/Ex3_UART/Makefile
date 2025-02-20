#compiler
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as

#compiler flags for debugging
CPU = -mcpu=cortex-m4
THUMB = -mthumb

#Target executable
TARGET = main.elf

#Source files
SRCS = main.c

#object files
OBJS = startup.o  main.o functions.o 



#Default target

all: $(TARGET)

#Rule to link object files into final executable
$(TARGET): $(OBJS)
	$(LD) -T linker.ld $(OBJS) -o $(TARGET)

#Rule to compile source file into object files
main.o: main.c
	$(CC) -c  -g $(CPU) $(THUMB) main.c -o main.o 

functions.o: functions.c
	$(CC) -c -g  $(CPU) $(THUMB) functions.c -o functions.o

startup.o: startup.s
	$(AS) -g $(CPU) startup.s -o startup.o

#Clean rule to remuve compiled files
clean:
	rm -f *.o
	rm -f *elf

