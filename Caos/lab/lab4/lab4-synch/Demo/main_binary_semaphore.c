#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "semphr.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction_Task1(void *pvParameters);
void vTaskFunction_Task2(void *pvParameters);

char buffer[1000];
int index = 0;

TickType_t xTicksToWait = portMAX_DELAY;


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    SemaphoreHandle_t xSemaphore = xSemaphoreCreateBinary();

	if (xSemaphore == NULL){
		
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
		xSemaphore,
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
		xSemaphore,
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

void generaStringa() {
    static char str[7];  // Buffer statico di massimo 6 caratteri + 1 per il terminatore '\0'
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    
    int lunghezza = (rand() % 7 )+ 1;  // Lunghezza casuale tra 0 e 6

    for (int i = 0; i < lunghezza; i++) {
        int index2 = rand() % (sizeof(charset) - 1);  // Ottieni un indice casuale nel charset
        str[i] = charset[index2];
    }

    str[lunghezza] = '\0';  // Terminatore null

	UART_printf(str);
	UART_printf("\n");

	int indexLibero=0;
	while (str[indexLibero] != '\0') {
		buffer[indexLibero+index] = str[indexLibero];
		indexLibero++;
	}
	buffer[indexLibero+index] = ' ';
	
	

	index = index + indexLibero + 1;
    return;
}


/* Task Function */
void vTaskFunction_Task1(void *pvParameters) {

    // Evita il warning per parametri non usati
    (void) pvParameters;

    SemaphoreHandle_t xSemaphore = pvParameters;


    for (int i = 0; i < 3; i++) {

        xSemaphoreTake( xSemaphore, 100 );

		UART_printf("Task1 is in the critical section\n");

		generaStringa();

		
		xSemaphoreGive( xSemaphore );

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTaskFunction_Task2(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

	SemaphoreHandle_t xSemaphore = pvParameters;

	// Delay for 1 second
    vTaskDelay(pdMS_TO_TICKS(1000));


    for (int i=0;i<3;i++) {

		xSemaphoreTake( xSemaphore, 100 );

		UART_printf("Task2 is in the critical section\n");

		generaStringa();

		
		xSemaphoreGive( xSemaphore );

        // Delay for 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

	UART_printf("\n\n\n\n");
	UART_printf(buffer);
}


