#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    	UART_init();

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

