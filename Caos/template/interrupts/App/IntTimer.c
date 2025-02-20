#include "FreeRTOS.h"
#include "semphr.h"


#include "IntTimer.h"

#include "SMM_MPS2.h"




void vInitialiseTimers( void )
{
	/* Clear interrupt. 
	 * INTCLEAR: This is the interrupt clear register timer 0. 
	 * Writing to INTCLEAR clears the interrupt flag for the timer, 
	 * acknowledging that the interrupt has been handled.
	 * */
	CMSDK_TIMER0->INTCLEAR = ( 1ul <<  0 );

	 /* Reload value is slightly offset from the other timer. */

	/* RELOAD holds the reload value for the timer 0. This value determines 
	 * the countdown starting point for the timer each time it resets.
	 *
	 * Our CPU runs at 25MH therefore configCPU_CLOCK_HZ defined in FreeRTOSConfig.h
	 * is 25000000. 
	 * */
	CMSDK_TIMER0->RELOAD   = ( configCPU_CLOCK_HZ / tmrTIMER_0_FREQUENCY ) + 1UL;

	/* CTRL is the control register for Timer 0. This register configures and controls various 
	 * aspects of the timer’s operation, including enabling the timer, setting the timer mode, 
	 * and configuring the timer’s interrupt.
	 *
	 * In our emulated board bit 3 enables the interrupts and bit 0 starts the timer.
	*/


	CMSDK_TIMER0->CTRL     = ( ( 1ul <<  3 ) | /* Enable Timer interrupt. */
						     ( 1ul <<  0 ) );  /* Enable Timer. */

	CMSDK_TIMER1->INTCLEAR = ( 1ul <<  0 );
	CMSDK_TIMER1->RELOAD   = ( configCPU_CLOCK_HZ / tmrTIMER_1_FREQUENCY ) + 1UL;
	CMSDK_TIMER1->CTRL     = ( ( 1ul <<  3 ) |
						     ( 1ul <<  0 ) );

	/* NVIC_SetPriority: is an ARM CMSIS function that configures the priority of a specific interrupt 
	 * in the Nested Vectored Interrupt Controller (NVIC).  
	 * It takes two parameters: the interrupt number and the priority level to assign.*/
	NVIC_SetPriority( TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY );
	NVIC_SetPriority( TIMER1_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY + 1 );
	
	
	/* NVIC_EnableIRQ is a function in the ARM CMSIS used to enable interrupts for a specific interrupt 
	 * source. It configures the Nested Vectored Interrupt Controller (NVIC) to allow the processor 
	 * to respond to a particular interrupt. 
	*/

	NVIC_EnableIRQ( TIMER0_IRQn );
	NVIC_EnableIRQ( TIMER1_IRQn );
}

