/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */

#include "timers.h"


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
int conta = 0;
void TaskA(void *pvParameters);
void TaskB(void *pvParameters);

TimerHandle_t periodic_timer;
TimerHandle_t one_shot_timer;
SemaphoreHandle_t sem;

void periodic_handler(void){

    xSemaphoreGive(sem);

}

void one_shot_handler(void){
    printf("GAME OVER\n");
}

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
   // vInitialiseTimers();


    
    xTaskCreate(TaskA,"TaskA",1000,NULL,1,NULL);
    xTaskCreate(TaskB,"TaskB",1000,NULL,2,NULL);

    periodic_timer = xTimerCreate("periodic_timer",pdMS_TO_TICKS(2000),pdTRUE,(void *)0, periodic_handler);
    one_shot_timer = xTimerCreate("one_shot_timer",pdMS_TO_TICKS(2000),pdFALSE,(void *)1, one_shot_handler);

    if (periodic_timer == NULL || one_shot_timer == NULL){
        printf("Error during timer creation\n");
        while(1);
    }

    sem = xSemaphoreCreateCounting(1,0);
    if(sem == NULL){
        printf("Error during timer creation\n");
        while(1);
    }

    xTimerStart(periodic_timer,0);
    xTimerStart(one_shot_timer,0);

    /* Start the scheduler. */
    vTaskStartScheduler();
    for( ; ; )
    {
    }

}

void TaskB(void *pvParameters){
    (void) pvParameters;

    while(1){
        xSemaphoreTake(sem,portMAX_DELAY);
        printf("Activation of Task B\n");
    }
}
void TaskA(void *pvParameters){
    (void) pvParameters;

    while(1){
        conta++;
        printf("Number of activation of Task A: %d\n",conta);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


