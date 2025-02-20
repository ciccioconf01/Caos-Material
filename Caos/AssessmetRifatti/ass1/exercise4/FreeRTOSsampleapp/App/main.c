#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void task_startup(void *pvParam);
void task1 (void *pvParam);
void task2 (void *pvParam);
void task3 (void *pvParam);

int count;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;
    UART_init();
	UART_printf("Main ready\n");

	xTaskCreate(task_startup,"task_startup",4096,NULL,9,NULL);

	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

void task_startup(void *pvParam){
	(void) pvParam;

	UART_printf("Task startup ready\n");
	count = 0;
	
	xTaskCreate(task1,"task1",4096,NULL,7,NULL);
	xTaskCreate(task2,"task2",4096,NULL,7,NULL);
	xTaskCreate(task3,"task3",4096,NULL,8,NULL);
	vTaskDelete(NULL);
}

void task1 (void *pvParam){
	(void) pvParam;
	char message[30];
	for(;;){
		count += 5;
		sprintf(message,"Task1, count value: %d\n",count);
		UART_printf(message);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	
}
void task2 (void *pvParam){
	(void) pvParam;
	char message[30];
	for(;;){
		count += 10;
		sprintf(message,"Task2, count value: %d\n",count);
		UART_printf(message);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	
}
void task3 (void *pvParam){
	(void) pvParam;
	UART_printf("Task 3 start\n");
	vTaskDelay(pdMS_TO_TICKS(1000));
	
	for(;;){

	}
}

