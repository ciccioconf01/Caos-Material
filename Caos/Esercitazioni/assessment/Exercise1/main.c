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
SemaphoreHandle_t sem;
extern uint32_t cnt;
int lvet=20;
int vet[20];

void TaskB(void *pvParameters){
    (void) pvParameters;


    while(1){
        xSemaphoreTake(sem,portMAX_DELAY);
        printf("Interrupt N: %d\n",cnt);
    }
    
}


void main( void )
{   

  

    /* Hardware initialisation.   */
    prvUARTInit();
    vInitialiseTimers();

    sem = xSemaphoreCreateCounting(1,0);
    if(sem==NULL){
        printf("errore\n");
    }

    xTaskCreate(TaskA, "TaskA", 1000, NULL, 1, NULL);
    xTaskCreate(TaskB, "TaskB", 1000, NULL, 2, NULL);
    

    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void TaskA(void *pvParameters){
    (void) pvParameters;
    int index1;
    int index2;
    int value;

    for(int i=0;i<lvet;i++){

        vet[i] = rand() %30;
    }

    while(1){

        index1 = rand() % 20;
        index2 = rand() % 20;

        value = vet[index1] * vet[index2];

        printf("Calculated value: %d\n",value);

        vTaskDelay(40);


    }
}

