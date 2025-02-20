/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"

/* Task priorities */

#define mainTASKA_STACK_SIZE ( configMINIMAL_STACK_SIZE + ( configMINIMAL_STACK_SIZE >> 1 ) )
#define mainTASKB_STACK_SIZE ( configMINIMAL_STACK_SIZE  )


#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )



static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}



void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    vInitialiseTimers();


    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}


