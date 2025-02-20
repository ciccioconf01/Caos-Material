/* Scheduler includes. */
#include "FreeRTOS.h"
#include "semphr.h"

/* Demo includes. */
#include "IntTimer.h"
/* Library includes. */
#include "SMM_MPS2.h"

#define tmrTIMER_0_FREQUENCY	( 2UL )


void vInitialiseTimers( void )
{
	CMSDK_TIMER0->INTCLEAR = ( 1ul <<  0 );
	CMSDK_TIMER0->RELOAD   = ( configCPU_CLOCK_HZ / tmrTIMER_0_FREQUENCY );
	CMSDK_TIMER0->CTRL     = ( ( 1ul <<  3 ) | /* Enable Timer interrupt. */
						     ( 1ul <<  0 ) );  /* Enable Timer. */
	NVIC_EnableIRQ( TIMER0_IRQn );
}

void TIMER0_Handler( void ){

	xSemaphoreGive(sem);
}
