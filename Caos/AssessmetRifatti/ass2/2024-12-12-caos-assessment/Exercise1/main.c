/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

#include "timers.h"

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
int counter = 0;
SemaphoreHandle_t xSemaphore;

void TimerFunction1(void){
    xSemaphoreGive(xSemaphore);
}

void TimerFunction2(void){
    printf("GAME OVER\n");
}


void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    //vInitialiseTimers();

    TimerHandle_t timer1;
    TimerHandle_t timer2;

    

    xTaskCreate(TaskA,"TaskA",4096,NULL,9,NULL);
    xTaskCreate(TaskB,"TaskB",4096,NULL,10,NULL);

    timer1 = xTimerCreate("Timer",pdMS_TO_TICKS(2000),pdTRUE,( void * ) 0, TimerFunction1);
    timer2 = xTimerCreate("Timer2",pdMS_TO_TICKS(2000),pdFALSE,( void * ) 1, TimerFunction2);

    xSemaphore = xSemaphoreCreateCounting( 10, 0 );

    if(timer1 == NULL || timer2 == NULL || xSemaphore == NULL){
        printf("Errore\n");
        return;
    }

    xTimerStart(timer1,0);
    xTimerStart(timer2,0);
    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void TaskA(void *pvParameters){
    (void) pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;){
        counter++;
        printf("Task A, counter: %d\n",counter);
        vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(1000) );
    }
}

void TaskB(void *pvParameters){
    for(;;){
        xSemaphoreTake(xSemaphore,portMAX_DELAY);
        printf("Task B\n");
        
    }
}


