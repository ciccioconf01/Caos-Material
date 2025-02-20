# Exercise 5 — makefile

You are given the following Makefile:

```makefile
CC = gcc
CFLAGS = -Wall -g
TARGET = program
SRC = main.c math_operations.c string_operations.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

```

Questions:

* What is the purpose of all the rules in this Makefile?
* Explain what the %.o: %.c rule does.
* What does the clean rule do, and when would you use it?


Aswer:
The makefile is designed for the phases of compilaton and link of the c files. Thanks to makefile with the command "make" we can execute the rules written in the label "all". The advantage of makefile is that it manage to understand if the proget has been already compiled and, if there are not changes, it don't recompile it, this lead to time save when we compile long project

The label all have 1 dependence and is used to call the label $(TARGET) (it's a variable that contain "program"), this label have also 1 dependence "$(OBJ)" (it's another variable that contain all .o files).
Thanks the last dependency we can run the rule under "%.o: %.c". With this rule we compile all .c files, and we create: main.o math_operations.o string_operations.o
After this execution we can run the rule under "$(TARGET): $(OBJ)" that is used for the linking process, in this phase all .o file created before will be linked and we create a single executable file.

How i said previously %.o: %.c it's used to indicate that for the creation of all .o files we need all .c files. Infact the rule under "%.o: %.c" is used for compiling all .c files

The clean rule is used for removing of all .o files and for removing the executable file program.
When we compile the project and we understand that there is a logical error in our code we need to eliminate our .o files and .elf files, we have to adjust the code and then we have to recompile all.
For the elimination phase is used the rule clean.