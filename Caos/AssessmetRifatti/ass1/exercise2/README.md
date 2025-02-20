# Exercise 2 - baremetal C programming and inline assembly

Write a baremetal C programm `main.c`that can be executed using qemu on ARM V7 to be executed on qemu-arm. The program is based on the following project:

```
├── Makefile
├── README.md
├── library.c
├── linker.ld
├── main.c
└── startup.s
```

The program must have the following specifications:

* It contains only the main function that defines an array of integers `v` of 10 integers
* An integer variable result `res`
* An inline assembly block that sums the elements of `v` and stores the results into `res`
* The result must be printed using the provided  `my_printf` function


Use the ARM v7 ISA reference list: [https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions](https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Instruction-Details/Alphabetical-list-of-instructions)