/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>



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
SemaphoreHandle_t sem;

int conta=0;

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
  

    sem = xSemaphoreCreateCounting(1,1);

    xTaskCreate(TaskA, "TaskA", 1000, NULL, 2, NULL);
    xTaskCreate(TaskB, "TaskB", 1000, NULL, 1, NULL);

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void TaskA(void *pvParameters){
    (void) pvParameters;

    while(1){
        vTaskDelay(300);
        printf("TASK A arrived\n");
        xSemaphoreTake(sem, portMAX_DELAY);
         vTaskDelay(50);
        conta++;
        printf("TASK A add 1 to count\n");

        xSemaphoreGive(sem);

        vTaskDelay(300);
    }
    

}
void TaskB(void *pvParameters){

    (void) pvParameters;

    while(1){
        vTaskDelay(200);
        printf("TASK B arrived\n");
        xSemaphoreTake(sem, portMAX_DELAY);
        vTaskDelay(400);
        conta++;
        printf("TASK B add 1 to count\n");
        xSemaphoreGive(sem);

        vTaskDelay(200);
    }
}


