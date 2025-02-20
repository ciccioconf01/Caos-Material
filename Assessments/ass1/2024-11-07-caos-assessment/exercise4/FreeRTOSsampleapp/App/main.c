#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MINIMAL_STACK_SIZE 20
#define MAX_PRIRITY 20

void vTaskFunction (void *pvParameters);
void vTaskFunction1 (void *pvParameters);
void vTaskFunction2 (void *pvParameters);
void vTaskFunction3 (void *pvParameters);

int count;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    	UART_init();

	xTaskCreate(
		vTaskFunction,
		"task",
		MINIMAL_STACK_SIZE,
		NULL,
		MAX_PRIRITY,
		NULL
	);

	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

void vTaskFunction (void *pvParameters){

	count = 0;

	xTaskCreate(
		vTaskFunction1,
		"task1",
		MINIMAL_STACK_SIZE,
		NULL,
		MAX_PRIRITY-2,
		NULL
	);
	xTaskCreate(
		vTaskFunction2,
		"task2",
		MINIMAL_STACK_SIZE,
		NULL,
		MAX_PRIRITY-2,
		NULL
	);
	xTaskCreate(
		vTaskFunction3,
		"task3",
		MINIMAL_STACK_SIZE,
		NULL,
		MAX_PRIRITY-1,
		NULL
	);

	vTaskDelete(NULL);
}

void vTaskFunction1 (void *pvParameters){
	for (;;){
		
		count = count + 5;
		UART_printf("Task 1, count: " + count);
		vTaskDelay(10);
	}
}

void vTaskFunction2 (void *pvParameters){
	for (;;){
	
		count = count + 10;
		UART_printf("Task 2, count:" + count);
		vTaskDelay(10);
	}


}

void vTaskFunction3 (void *pvParameters){
	vTaskDeley(1);
	UART_printf("Task3");

	for (;;){
		
	}


}
