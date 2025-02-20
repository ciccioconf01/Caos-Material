/* Scheduler includes. */
#include "FreeRTOS.h"
#include "semphr.h"

/* Demo includes. */
#include "IntTimer.h"
/* Library includes. */
#include "SMM_MPS2.h"

#define tmrTIMER_0_FREQUENCY	( 2UL )

#define tmrTIMER_1_FREQUENCY	( 5UL )


extern SemaphoreHandle_t sem;
volatile uint32_t cnt = 0;

void vInitialiseTimers( void )
{
	

	CMSDK_TIMER1->INTCLEAR = ( 1ul <<  0 );
	CMSDK_TIMER1->RELOAD   = ( configCPU_CLOCK_HZ / tmrTIMER_1_FREQUENCY );
	CMSDK_TIMER1->CTRL     = ( ( 1ul <<  3 ) | /* Enable Timer interrupt. */
						     ( 1ul <<  0 ) );  /* Enable Timer. */
	NVIC_EnableIRQ( TIMER1_IRQn );
}

void TIMER1_Handler( void ){

	BaseType_t x=pdFALSE;

	CMSDK_TIMER1->INTCLEAR = ( 1ul <<  0 );
	cnt++;
	xSemaphoreGiveFromISR(sem,&x);
	portEND_SWITCHING_ISR(x);

}

