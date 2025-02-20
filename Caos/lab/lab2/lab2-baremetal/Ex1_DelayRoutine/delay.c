#include "delay.h"

void delay_routine_1(void){
    __asm(
        "mov r1,#11 \n"
        "loop: \n"
        "sub r1,r1,#1 \n"
        "cmp r1,#0 \n"
        "bne loop \n"


    );
}

void delay_routine_2(unsigned int delay_counter){
    __asm(
        "mov r0, %0 \n"    // Move the value of delay_counter into r0
        "loop2: \n"
        "sub r0,r0,#1 \n"
        "cmp r0,#0 \n"
        "bne loop2 \n"

        :                   // No output
        : "r" (delay_counter) // Input: delay_counter
    );
}