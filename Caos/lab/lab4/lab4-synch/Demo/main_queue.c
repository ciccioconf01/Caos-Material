#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction_Producer(void *pvParameters);
void vTaskFunction_Consumer(void *pvParameters);

int N=100;
const UBaseType_t length = 20;
const UBaseType_t size = sizeof(int);

TickType_t TicksToWait = portMAX_DELAY;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

	QueueHandle_t handler = xQueueCreate( length, size);

	if (handler == NULL){
		
		UART_printf("Errore nella creazione della coda\n");
	}


	xTaskCreate(
		// Function which implements the task
		vTaskFunction_Producer,
		// Name of the task (debug purposes, not used by the kernel)
		"Task_Producer",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		handler,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFunction_Consumer,
		// Name of the task (debug purposes, not used by the kernel)
		"Task_Consumer",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		handler,
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
void vTaskFunction_Producer(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;
	char message[100];

	QueueHandle_t handler = pvParameters;

    for (int i=0;i<N;i++) {

		int random_number = rand() %1000;
		int *pointer_toRandom_Number = &random_number;

		BaseType_t xStatus = xQueueSend( handler,  pointer_toRandom_Number,  TicksToWait );

        // Task code: print a message
		if (xStatus == pdPASS){
			sprintf(message, "Number WRITING: %d\n", *pointer_toRandom_Number);
			UART_printf(message);
        } else {
            UART_printf("Queue full, could not send number\n");
        }
        

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunction_Consumer(void *pvParameters) {

	(void) pvParameters;
	char message[100];

	QueueHandle_t handler = pvParameters;

	int pvBuffer;
	int number;
	int conta=0;
    for (int i = 0;i<N;i++) {
		// Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));

		BaseType_t xStatus = xQueueReceive(handler, &pvBuffer, TicksToWait);

        if (xStatus == pdPASS) {
            if (pvBuffer % 7 == 0) {
                conta++;
            }
			sprintf(message, "Number READING: %d\n", pvBuffer);
            UART_printf(message);
        } else {
            UART_printf("Queue empty, could not receive number\n");
        }

        
    }

	sprintf(message, "Total multiplies of 7: %d\n", conta);
	UART_printf(message);
}
