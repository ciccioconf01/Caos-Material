#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include "semaphore.h"
#define MinimalStack 4096
#define mainPriority 9

SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xSemaphore2;
TimerHandle_t xTimer;
int counter = 0;

void TaskA(void *pvParameters);
void TaskB(void *pvParameters);
void TaskC(void *pvParameters){

	int value = counter;
	int result = 0;

	__asm__ (
		"ldr r0,=%0\n"
		"ldr r1,[r0]\n" //value of counter
		"ldr r2,=%1\n"	//result 
		"mov r3,r1\n"	//index
		"mov r4,r1\n"	//accumulator
		"loop:\n"
		"cmp r3,#0\n"
		"beq exit_loop\n"
		"sub r3,r3,#1\n"
		"mul r4, r4, r3\n"
		"b loop\n"
		"exit_loop:\n"
		"str r4,[r2]\n"
		:
		: "r" (value) , "r" (result)
		: "r0", "r1" , "r2", "r3", "r4", "r5"
	);

	printf("Factorial: %d\n",result);
}



int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    	UART_init();
	


    xSemaphore = xSemaphoreCreateCounting( 1, 1 );
	xSemaphore2 = xSemaphoreCreateCounting( 1, 0 );
	if(xSemaphore == NULL || xSemaphore2 == NULL){
		return -1;
	}

	xTaskCreate(TaskA,"TaskA",MinimalStack,NULL,mainPriority-1,NULL);
	xTaskCreate(TaskB,"TaskB",MinimalStack,NULL,mainPriority-1,NULL);
	xTimer = xTimerCreate("Timer",pdMS_TO_TICKS(700),pdTRUE,(void *) 0, TaskC);
	xTimerStart(xTimer,0);
	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

void TaskA(void *pvParameters){
	(void) pvParameters;
	TickType_t xLastWakeTime;
	xLastWakeTime= xTaskGetTickCount();


	for(;;){

		xSemaphoreTake(xSemaphore,portMAX_DELAY);
		for(int i =0; i<50;i++){
			counter++;
		}
		printf("TaskA, counter: %d",counter);
		xSemaphoreGive(xSemaphore2);
		vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(500) );
	}

}
void TaskB(void *pvParameters){
	(void) pvParameters;
	TickType_t xLastWakeTime;
	xLastWakeTime= xTaskGetTickCount();


	for(;;){

		xSemaphoreTake(xSemaphore2,portMAX_DELAY);
		for(int i =0; i<50;i++){
			counter--;
		}
		printf("TaskB, counter: %d",counter);
		xSemaphoreGive(xSemaphore);
		vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(500) );
	}

}


