#include "FreeRTOS.h"
#include "task.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction(void *pvParameters);
void vTaskFunction2(void *pvParameters);
void vTaskFib(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

//	xTaskCreate(
		// Function which implements the task
//		vTaskFunction,
		// Name of the task (debug purposes, not used by the kernel)
//		"Task1",
		// Stack to allocate to the task
//		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
//		NULL,
		// Priority assigned to the task
//		mainTASK_PRIORITY,
		// Task handle. Not required
//		NULL
//	);

//	xTaskCreate(
		// Function which implements the task
//		vTaskFunction2,
		// Name of the task (debug purposes, not used by the kernel)
//		"Task2",
		// Stack to allocate to the task
//		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
//		NULL,
		// Priority assigned to the task
//		mainTASK_PRIORITY,
		// Task handle. Not required
//		NULL
//	);

	xTaskCreate(
		// Function which implements the task
		vTaskFib,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskFib1",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World exampNULL,
		NULL,
		// Priority assigned to the task
		mainTASK_PRIORITY,
		// Task handle. Not required
		NULL
	);

	xTaskCreate(
		// Function which implements the task
		vTaskFib,
		// Name of the task (debug purposes, not used by the kernel)
		"TaskFib2",
		// Stack to allocate to the task
		configMINIMAL_STACK_SIZE,
		// Parameter passed to the task. Not needed for Hello World example
		NULL,
		// Priority assigned to the task
		mainTASK_PRIORITY-1,
		// Task handle. Not required
		NULL
	);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

/* Task Function */
void vTaskFunction(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

    for (;;) {

        // Task code: print a message
        UART_printf("Hello, World!\n");

        // Delay for 1 second
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void vTaskFunction2(void *pvParameters) {

	// Avoid warning about unused pvParameters
	(void) pvParameters;

    for (;;) {

        // Task code: print a message
        UART_printf("Hello, World! From Task 2!\n");

        // Delay for 1 second
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void intToStr(unsigned int num, char *str) {
    int i = 0;

    // Converti numero in stringa
    do {
        str[i++] = (num % 10) + '0'; // Prendi il resto e convertilo in carattere
        num /= 10; // Dividi per 10
    } while (num > 0);

    str[i] = '\n'; // Aggiungi il carattere di nuova linea
    str[i + 1] = '\0'; // Termina la stringa

    // Inverti la stringa
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}


void vTaskFib(void *pvParameters) {

    (void) pvParameters;

    int n1 = 0;
	char str[50];


	intToStr(n1,str);
    UART_printf(str);

    
    int n2 = 1;


    intToStr(n2,str);
    UART_printf(str);

    
    int n3 = 0;

    for (int i = 0; i < 10; i++) {
        n3 = n2 + n1;
        n1 = n2;
        n2 = n3;

        intToStr(n3,str);
        UART_printf(str);

    }

	vTaskDelete(NULL);


}
