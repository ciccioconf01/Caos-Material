#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>


#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

/*
 * Define two software timers. One timer is one shot and the 
 * other is repetitive 
 */

static TimerHandle_t one_shot_timer = NULL;
static TimerHandle_t auto_reload_timer = NULL;

/* Called when one of the timers expires 
 *
 * The only parameter of this function identifies the
 * calling timer. This is useful when multiple timers
 * call the same function.
 *
 * */

void myTimerCallback(TimerHandle_t xTimer) {

	/* Print if timer 0 expires */
	if ( (uint32_t) pvTimerGetTimerID(xTimer) == 0) {
		UART_printf("Timer 0 Expired\n");	
	}

	/* Print if timer 1 expires */
	if ( (uint32_t) pvTimerGetTimerID(xTimer) == 1) {
		UART_printf("Timer 1 Expired\n");	
	}
}


void TaskA(void *pvParameters);

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
	
	UART_printf("Ready to run the scheduler\n");

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}


/* Task A */
void TaskA(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

	// Create a one shot timer
	one_shot_timer = xTimerCreate(
				"One-shot timer", 		//Name of timer
				pdMS_TO_TICKS(2000), 	// Period of the timer in ticks
				pdFALSE,			// Auto-reload
				(void *) 0, 			//Timer ID. We need to cas as a void 
								//pointer even if it is not a pointer.
				myTimerCallback	    		//CallBackFunction 
			);
	//Since timer creation requires the use of memory this operation can fail.

	// Create an auto-reload  timer
	auto_reload_timer = xTimerCreate(
				"One-shot timer", 		//Name of timer
				pdMS_TO_TICKS(1000), 	// Period of the timer in ticks
				pdTRUE,				// Auto-reload
				(void *) 1, 			//Timer ID. We need to cas as a void 
								//pointer even if it is not a pointer.
				myTimerCallback	    		//CallBackFunction 
			);
	
	if (one_shot_timer == NULL || auto_reload_timer == NULL) {
		UART_printf ("ERROR: impossible to create timer\n");
	}
	vTaskDelay(pdMS_TO_TICKS(1000));
	UART_printf("StartingTimers\n");

	/* Start the two timers */
	xTimerStart(one_shot_timer,portMAX_DELAY);
	xTimerStart(auto_reload_timer,portMAX_DELAY);

	/* Delete the task to show that timers work even if there is no task running */
	vTaskDelete(NULL);
}



