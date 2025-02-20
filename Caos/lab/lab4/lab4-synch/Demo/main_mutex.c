#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "semphr.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction_Task1(void *pvParameters);
void vTaskFunction_Task2(void *pvParameters);

int shared_counter=0;

TickType_t xTicksToWait = portMAX_DELAY;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

	if (xMutex == NULL){
		
		UART_printf("Errore nella creazione della coda\n");
	}


	xTaskCreate(
		// Function which implements the task
		vTaskFunction_Task1,
		// Name of the task (debug purposes, not used by the kernel)
		"Task1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xMutex,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFunction_Task2,
		// Name of the task (debug purposes, not used by the kernel)
		"Task2",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		xMutex,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);


	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

/* Task Function */
void vTaskFunction_Task1(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

	SemaphoreHandle_t xMutex = pvParameters;

    for (;;) {
		
		xSemaphoreTake(xMutex, xTicksToWait);
		UART_printf("Task1 is in the critical section\n");
		shared_counter++;
		xSemaphoreGive(xMutex);
        

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunction_Task2(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

	SemaphoreHandle_t xMutex = pvParameters;

    for (;;) {
		
		xSemaphoreTake(xMutex, xTicksToWait);
		UART_printf("Task2 is in the critical section\n");
		shared_counter++;
		xSemaphoreGive(xMutex);
        

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
