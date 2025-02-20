#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
//------------------
#include "uart.h"
#include <stdio.h> 
//------------------

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

TimerHandle_t timer = NULL;
int contatore = 0;
char message[30];

void handler(){



    contatore ++;
    sprintf(message,"Valore del contatore: %d\n",contatore);
    UART_printf(message);
}

void Task1(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    xTaskCreate(Task1, "Task", 1000, NULL, mainTASK_PRIORITY+1, NULL);

    vTaskStartScheduler();
    while (1);
}

void Task1(void *pvParameters){

    (void) pvParameters;

    timer = xTimerCreate("timer1",pdMS_TO_TICKS(2000),pdTRUE, (void *)0,handler);

    if (timer!=NULL){
        xTimerStart(timer,0);
    }
    for(;;){

    }
}
