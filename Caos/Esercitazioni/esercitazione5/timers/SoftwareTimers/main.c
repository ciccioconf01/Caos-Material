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

TimerHandle_t timer;
QueueHandle_t queue;
int contatore = 0;
typedef struct{
    char message[40];
}message;


void handler(){
    message m;
    contatore++;
    sprintf(m.message,"messaggio: %d\n",contatore);
    if(xQueueSend(queue,&m,portMAX_DELAY)==pdPASS){
        //UART_printf("messagio mandato");
    }
    else{
        //UART_printf("errore: coda piena\n");
    }

}

void task1(void *pvParameters);

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    queue = xQueueCreate(10,sizeof(message));
    if(queue==NULL){
        UART_printf("errore");
    }

    xTaskCreate(task1, "task1", 1000, NULL, mainTASK_PRIORITY+1, NULL);
    timer = xTimerCreate("timer",pdMS_TO_TICKS(3000),pdTRUE,(void*) 0, handler);
    if(timer != NULL){
        xTimerStart(timer,0);
    }

    vTaskStartScheduler();

    while (1);
}

void task1(void *pvParameters){
    (void) pvParameters;
    message m;
    for(;;){
        if(xQueueReceive(queue,&m,portMAX_DELAY)==pdPASS){
            UART_printf(m.message);
        }
        else{
            UART_printf("errore in lettura");
        }

        vTaskDelay(100);
    }
}