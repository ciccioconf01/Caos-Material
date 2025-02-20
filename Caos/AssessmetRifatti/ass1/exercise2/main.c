#include <stdint.h>
#include "library.h"
/* This is a function to print strings using UART */
extern void my_printf(const char *s); 

int main(void) {
    int array[10] = {0,1,2,3,4,5,6,7,8,9};
    int result;
    __asm__ (
        "ldr r0,=%0\n"
        "ldr r1,=%1\n"
        "mov r2,#0\n"//index
        "mov r3,#0\n"//accumulator
        "mov r4,#10\n" //vet len
        "loop:\n"
        "cmp r2,r4\n"
        "beq exit_loop\n"
        "ldr r5, [r0,r2,lsl #2]\n"
        "add r3,r3,r5\n"
        "add r2,r2,#1\n"
        "b loop\n"
        "exit_loop:\n"
        "str r3,[r1]\n"
        "b .\n"
        :
        : "r" (array), "r" (&result)
        : "r0" , "r1" , "r2" , "r3" , "r4" , "r5"
    );

    char str[10];
    intToStr(result,str);
    my_printf (str);
    return 0;
}


