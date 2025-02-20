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

SemaphoreHandle_t sem;

int matA[3][3];
int matB[3][3]; 
int nr = 3;
int nc = 3;
int conta = 0;

void TaskA (void *pvParameters);

void TaskB (){

    while(1){
        xSemaphoreTake(sem,10000);
        conta++;
        printf("Interrupt n: %d",conta);
    }
    
}

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    vInitialiseTimers();

    sem = xSemaphoreCreateBinary();
    /* Start the scheduler. */
    vTaskStartScheduler();
    xTaskCreate(TaskA,"TaskA",1000,NULL,1,NULL);
    xTaskCreate(TaskB,"TaskB",1000,NULL,2,NULL);

    for( ; ; )
    {
    }

}

void TaskA(void * pvParameters){
    (void) pvParameters;

    int matc[3][3];

    for(int i =0;i<nr;i++){
        for(int j=0;j<nc;j++){
            matA[i][j] = 1;
            matB[i][j] = 1;
        }
    }

    int k =0;
    int z =0;
    int value;
    int value2;
    int i=0;
    int j=0;

    int partial1=0;
    int partial2=0;
    int partial3=0;

    char message[50];

    while (1){
        
        for(i=0;i<nr;i++){
            for(j=0;j<nc;j++){
                value = matA[i][j];
                value2 = matB[k][z];

                if (k==0){
                    partial1 = value*value2;
                }
                else if (k==1){
                    partial2 = value*value2;
                }
                else{
                    partial3 = value*value2;
                }
                k++;

                if(k==3){
                    k=0;
                }

            }

            z++;
            matc[i][j]= partial1 + partial2 + partial3;
        }

        sprintf(message,"%d %d %d\n%d %d %d\n%d %d %d",matc[0][0], matc[0][1], matc[0][2],matc[1][0], matc[1][1], matc[1][2],matc[2][0], matc[2][1], matc[2][2]);
        //UART_printf(message);
        vTaskDelay(20);
    }
}


