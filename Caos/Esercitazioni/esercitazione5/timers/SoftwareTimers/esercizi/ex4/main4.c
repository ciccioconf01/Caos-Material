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

void OrderPickerTask(void *pvParameters) {
   /* your code goes here */
}

void produttore(void *pvParameters);
void processatore(void *pvParameters);
void registratore(void *pvParameters);

QueueHandle_t queue_pp;
QueueHandle_t queue_pr;
TimerHandle_t timer;
SemaphoreHandle_t sem;

typedef struct{
    int temperature_value;
    int alarm; //0 no alarm, 1 alarm
}message_pp;

typedef struct{
    int media;
    char message[30];
}message_pr;

void handler(){

    xSemaphoreGive(sem);
    

}


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    sem = xSemaphoreCreateBinary();

    if(sem == NULL){
        UART_printf("errore nella creazione del semaforo");
    }

    queue_pp = xQueueCreate(10, sizeof(message_pp));
    queue_pr = xQueueCreate(10, sizeof(message_pr));

    if (queue_pp == NULL || queue_pr == NULL){
        UART_printf("errore creazione code");
    }
    timer = xTimerCreate("timer",pdMS_TO_TICKS(3000),pdTRUE,(void*)0,handler);
   
    xTaskCreate(produttore, "produttore", 1000, NULL, mainTASK_PRIORITY+1, NULL);
    xTaskCreate(processatore, "processatore", 1000, NULL, mainTASK_PRIORITY+1, NULL);
    xTaskCreate(registratore, "registratore", 1000, NULL, mainTASK_PRIORITY+1, NULL);

     if (timer != NULL){
        xTimerStart(timer,0);
    }

    vTaskStartScheduler();
    while (1);
}

void registratore(void *pvParameters){

    (void) pvParameters;
    int contaAllarmi=0;
    message_pr m2;
    char message[30];

    while(1){

        if(xQueueReceive(queue_pr,&m2,portMAX_DELAY)==pdPASS){
            if(m2.media == -1){
                contaAllarmi++;
                sprintf(message,"Allarme N: %d rilevato\n",contaAllarmi);
                UART_printf(message);
            }
            else{
                sprintf(message,"Media temperatura aggiornata: %d\n", m2.media);
                UART_printf(message);
            }
        }
        else{
            //UART_printf("errore");
        }


    }
}

void processatore(void *pvParameters){
    (void) pvParameters;
    int n = 0;
    int somma = 0;
    int media = 0;
    message_pp m;
    message_pr m2;

    while(1){
        if (xQueueReceive(queue_pp,&m,portMAX_DELAY)==pdPASS){
            if(m.temperature_value == -1){
                if(m.alarm == 1){
                    sprintf(m2.message,"Messaggio di allarme");
                    m2.media = -1;
                    if (xQueueSend(queue_pr,&m2,portMAX_DELAY)==pdPASS){
                        //UART_printf("messaggio mandato");
                    }
                    else{
                        //UART_printf("errore");
                    }
                }
                
            }

            else{
                
                n++;
                somma = somma + m.temperature_value;
                media = somma/n;
                m2.media = media;
                if (xQueueSend(queue_pr,&m2,portMAX_DELAY)==pdPASS){
                    //UART_printf("messaggio mandato");
                }
                else{
                    //UART_printf("errore");
                }

            }
        }
        else{
            //UART_printf("Error");
        }


    }
}


void produttore(void *pvParameters){
    
    (void) pvParameters;
    int n;
    int value;
    message_pp m ;
    while (1){
        xSemaphoreTake(sem,portMAX_DELAY);
        n = rand()%2;

        if(n == 0){
            value = rand() %30 + 10;
            m.temperature_value = value;
            m.alarm = -1;
        }
        else{
            m.temperature_value = -1;
            m.alarm = rand()%2;
        }

        if(xQueueSend(queue_pp,&m,portMAX_DELAY)==pdPASS){
            //UART_printf("message sent");
        }
        else{
            //UART_printf("error");
        }

        }

    }
    



