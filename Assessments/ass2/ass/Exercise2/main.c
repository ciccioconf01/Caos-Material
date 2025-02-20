/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"
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

void TaskA(void *pvParameters);
void TaskB(void *pvParameters);
void TaskC(void *pvParameters);
void TaskD(void *pvParameters);

SemaphoreHandle_t sem1;
SemaphoreHandle_t sem2;
SemaphoreHandle_t sem3;

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    //vInitialiseTimers();

    sem1 = xSemaphoreCreateCounting(1,1);
    sem2 = xSemaphoreCreateCounting(1,0);
    sem3 = xSemaphoreCreateCounting(1,0);
    
    if (sem1 == NULL || sem2 == NULL || sem3 == NULL){
        printf("Error, bad semaphore creation\n");
        while(1);
    }

    xTaskCreate("TaskA",TaskA,1000,NULL,1,NULL);
    xTaskCreate("TaskB",TaskB,1000,NULL,1,NULL);
    xTaskCreate("TaskC",TaskC,1000,NULL,1,NULL);
    xTaskCreate("TaskD",TaskD,1000,NULL,1,NULL);
    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void TaskA(void *pvParameters){

    (void) pvParameters;

    while(1){
    
        xSemaphoreTake(sem1,portMAX_DELAY);
        printf("TASK A\n");
        xSemaphoreGive(sem2);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}

void TaskB(void *pvParameters){

    (void) pvParameters;

    while(1){
        xSemaphoreTake(sem2,portMAX_DELAY);
        printf("TASK B\n");
        xSemaphoreGive(sem3);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}

void TaskC(void *pvParameters){

    (void) pvParameters;

    while(1){
        xSemaphoreTake(sem2,portMAX_DELAY);
        printf("TASK C\n");
        xSemaphoreGive(sem3);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}

void TaskD(void *pvParameters){

    (void) pvParameters;

    while(1){
        xSemaphoreTake(sem3,portMAX_DELAY);
        printf("TASK D\n");
        xSemaphoreGive(sem1);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}


