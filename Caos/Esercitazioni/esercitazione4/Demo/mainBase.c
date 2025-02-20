#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//------------------
#include "uart.h"
#include <stdio.h> 
//------------------

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void OrderPickerTask(void *pvParameters) {
   /* your code goes here */
}


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    /* your code goes here */
    // sample
    //xTaskCreate(OrderPickerTask, "OrderPicker", 1000, NULL, mainTASK_PRIORITY+1, NULL);

    vTaskStartScheduler();
    while (1);
}
