/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */

#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )


/* GLOBAL VARIABLES */



static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}

void TaskA(void *pvParameters);
void TaskB(void *pvParameters);
SemaphoreHandle_t xSemaphore;
extern int counter = 0;


void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    vInitialiseTimers();

    xTaskCreate(TaskA, "TaskA",4096,NULL,5,NULL);
    xTaskCreate(TaskB, "TaskB",4096,NULL,6,NULL);

    xSemaphore = xSemaphoreCreateCounting( 10, 0 );

    if(xSemaphore==NULL){
        printf("errore\n");
        return;
    }

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void TaskB(void *pvParameters){
    xSemaphoreTake(xSemaphore,portMAX_DELAY);
    printf("Execution number: %d\n",counter);
}

void TaskA(void *pvParameters){
    (void) pvParameters;

    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;){
        printf("TaskA begin\n");
        for(int i=0;i<100000;i++){

        }
        printf("TaskA end");

        vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(20) );
    }
    

}


