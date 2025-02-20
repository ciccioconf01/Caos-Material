#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Define priority for the two tasks. 
 * The sampling task is set to a higher priority to make sure
 * it is timely executed.
 *
 * */

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define sampleTASK_PRIORITY    ( tskIDLE_PRIORITY + 3 )

void TaskA(void *pvParameters);
void SampleFunction(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    	UART_init();

	xTaskCreate(
		// Function which implements the task
		TaskA,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskA",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		NULL,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);
	
	xTaskCreate(
		// Function which implements the task
		SampleFunction,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskA",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		NULL,
		// Priority assigned to the task
		sampleTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}


/* Task A */
void TaskA(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;
	char message[100];
	TickType_t t;
	// This task performs busy waiting to emulate a CPU intensive task
	for (;;) {
		long int i;
		for (i=0;i<LONG_MAX;i++); 
		t = xTaskGetTickCount();
		sprintf(message,"Busiwaited %lu ticks\n", t);
		UART_printf(message);
    	}
}


/* Sampled function */
void SampleFunction(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

	for (;;) {
		// Task code: print a messagedd
		UART_printf("Sampled\n");

		/* Delay for 220 ms second
		 * Function pdMS_TO_TICKS converts ms into 
		 * ticks adapting to the available.
		*/

		vTaskDelay(pdMS_TO_TICKS(1000));
    	}
}

