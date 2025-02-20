#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include <stdio.h>

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void creator(void *pvParameters);
void pack(void *pvParameters);
void deliver(void *pvParameters);
void logger(void *pvParameters);
QueueHandle_t xQueue1, xQueue2;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    xQueue1 = xQueueCreate( 10, sizeof( int ) );
    xQueue2 = xQueueCreate( 10, sizeof( int ) );

    if(xQueue1 == NULL || xQueue2 == NULL){
        UART_printf("errore\n");
        return -1;
    }

	xTaskCreate(creator,"creator",configMINIMAL_STACK_SIZE,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(pack,"pack",configMINIMAL_STACK_SIZE,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(deliver,"deliver",configMINIMAL_STACK_SIZE,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(logger,"logger",configMINIMAL_STACK_SIZE,NULL,mainTASK_PRIORITY,NULL);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

void creator(void *pvParameters){

    (void) pvParameters;
    UART_printf("Start creator\n");
    for(;;){
        int value = rand() % 3; //0=item0, 1=item1, 2=item2
        if( xQueueSend( xQueue1,&value,portMAX_DELAY ) != pdPASS ){
            
            UART_printf("error during sending\n");
        }

        UART_printf("Item sent by creator\n");

        vTaskDelay(1000);
    }
}

void pack(void *pvParameters){

    (void) pvParameters;
    int val;
    int counter=0;
    char message[100];
    UART_printf("Start packer\n");

    for(;;){
        if( xQueueReceive( xQueue1,&val,portMAX_DELAY) == pdPASS ){

            counter++;
            sprintf(message,"Item packed, total item packed: %d\n",counter);
            UART_printf(message);

        }


        if( xQueueSend( xQueue2,&val,portMAX_DELAY ) != pdPASS ){
                
                UART_printf("error during sending\n");
            }

            UART_printf("Item sent to deliver\n");

        vTaskDelay(1200);

    }
    
    

}
void deliver(void *pvParameters){

    (void) pvParameters;
    int val;
    UART_printf("Start deliver\n");
    for(;;){
        if( xQueueReceive( xQueue2,&val,portMAX_DELAY) == pdPASS ){

            UART_printf("Delivering...\n");

        }

        vTaskDelay(1300);
    }

    
}
void logger(void *pvParameters){
    (void) pvParameters;

    while(1){
        UART_printf("The sistem is ok\n");
        vTaskDelay(10000);
    }
}
