#include "FreeRTOS.h"
#include "task.h"

#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void vTaskFunction1(void *pvParameters);
void vTaskFunction2(void *pvParameters);
void vTaskFunction3(void *pvParameters);





int main(){
    UART_init();

    xTaskCreate(
        vTaskFunction1,
        "Task main",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainTASK_PRIORITY,
        NULL
    );

    vTaskStartScheduler();

    for( ; ; );
}

void vTaskFunction1(void *pvParameters){

    char * message1 = "Hello from Task 1\n";
    char * message2 = "Hello from Task 2\n";

    for(;;){
        xTaskCreate(
            vTaskFunction2,
            "Task2",
            configMINIMAL_STACK_SIZE,
            message1,
            mainTASK_PRIORITY,
            NULL
        );

        xTaskCreate(
            vTaskFunction3,
            "Task2",
            configMINIMAL_STACK_SIZE,
            message2,
            mainTASK_PRIORITY,
            NULL
        );
    }


    vTaskDelete(NULL);
}

void vTaskFunction2(void *pvParameters){

    char *message = pvParameters;

        UART_printf(message);
    
}

void vTaskFunction3(void *pvParameters){
        char *message = pvParameters;

        UART_printf(message);
}

