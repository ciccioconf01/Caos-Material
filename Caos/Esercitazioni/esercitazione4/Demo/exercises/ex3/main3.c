#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//------------------
#include "uart.h"
#include <stdio.h> 
//------------------

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void user_command_interface(void *pvParameters);
void HVACcontroller(void *pvParameters);
void lighting_system(void *pvParameters);
void security_system(void *pvParameters);
void logger_system(void *pvParameters);
void increase_hour(void *pvParameters);

QueueHandle_t hva_queue;
QueueHandle_t lighting_queue;
QueueHandle_t security_queue;

SemaphoreHandle_t mutex_hour;
SemaphoreHandle_t mutex_stateLight;
SemaphoreHandle_t mutex_securityStatus;



typedef struct{
    int value; //temperature to set
}hva_message;

typedef struct{
    int value; //1 to turn on the light
}lighting_message;

typedef struct{
    int value; //1 to lock the door

}security_message;

int home_temperature;
int hourDay;
int stateLight; //0 off, 1 on
int securityStatus; //0 lock, 1 unlock

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    mutex_hour = xSemaphoreCreateMutex();
    mutex_stateLight = xSemaphoreCreateMutex();
    mutex_securityStatus = xSemaphoreCreateMutex();

    hva_queue = xQueueCreate(10,sizeof(hva_message));
    lighting_queue = xQueueCreate(10,sizeof(lighting_message));
    security_queue = xQueueCreate(10,sizeof(security_queue));

    if(mutex_hour == NULL || hva_queue == NULL || lighting_queue==NULL || security_queue==NULL){
        UART_printf("ERROR\n");
    }

    xTaskCreate(user_command_interface,"user_command_interface",1000,NULL,mainTASK_PRIORITY+1,NULL);
    xTaskCreate(HVACcontroller,"HVACcontroller",1000,NULL,mainTASK_PRIORITY+2,NULL);
    xTaskCreate(lighting_system,"lighting_system",1000,NULL,mainTASK_PRIORITY+2,NULL);
    xTaskCreate(security_system,"security_system",1000,NULL,mainTASK_PRIORITY+2,NULL);
    xTaskCreate(logger_system,"logger_system",1000,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(increase_hour,"increase_hour",1000,NULL,mainTASK_PRIORITY,NULL);

    vTaskStartScheduler();
    while (1);
}

void security_system(void *pvParameters){
    (void) pvParameters;

    security_message s;

    for(;;){
        if(xQueueReceive(security_queue,&s,portMAX_DELAY)==pdPASS){

            xSemaphoreTake(mutex_securityStatus,portMAX_DELAY);
            if(s.value==0 && securityStatus==1){
                UART_printf ("UNLOCKING DOORS\n");
                securityStatus = 0;
            }
            else if(s.value==1 && securityStatus==0){
                UART_printf ("LOCKING DOORS\n");
                securityStatus = 1;
            }
            xSemaphoreGive(mutex_securityStatus);

        }
        else{
            //UART_printf("ERROR");
        }

        vTaskDelay(1000);
    }

}


void increase_hour(void *pvParameters){
    for(;;){

        xSemaphoreTake(mutex_hour, portMAX_DELAY);
        if (hourDay==23){
            hourDay = 0;
        }
        else{
            hourDay++;
        }
        xSemaphoreGive(mutex_hour);

        vTaskDelay(10000);
    }
}

void lighting_system(void *pvParameters){
    (void) pvParameters;
    int count;
    lighting_message l;

    for(;;){

        

        count = uxQueueMessagesWaiting(lighting_queue);
        if (count == 0){
            xSemaphoreTake(mutex_hour,portMAX_DELAY);
            if (hourDay > 20 || hourDay < 7){
                xSemaphoreTake(mutex_stateLight,portMAX_DELAY);
                if (stateLight == 1){
                    stateLight = 0;
                }
                xSemaphoreGive(mutex_stateLight);

            }
            xSemaphoreGive(mutex_hour);
        }

        

        else{
            if(xQueueReceive(lighting_queue,&l, portMAX_DELAY)==pdPASS){
                xSemaphoreTake(mutex_stateLight,portMAX_DELAY);
 
                if(l.value==1 && stateLight == 0){
                    UART_printf("TURNING ON LIGHTS");
                    stateLight = 1;
                }

                else if(l.value==0 && stateLight == 1){
                    UART_printf("TURNING OFF LIGHTS");
                    stateLight = 0;
                }

                xSemaphoreGive(mutex_stateLight);

            }
            else{
                //UART_printf("ERROR");
            }
        }

        vTaskDelay(1000);
        

    }
}


void HVACcontroller(void *pvParameters){
    (void) pvParameters;

    hva_message h;
    char message[50];

    for(;;){
        if(xQueueReceive(hva_queue,&h,portMAX_DELAY)==pdPASS){

            sprintf(message,"The new home temperature is: %d\n",h.value);
            UART_printf(message);
        }
        else{
            //UART_printf("ERROR");
        }
        vTaskDelay(1000);
    }
}



void user_command_interface(void *pvParameters){
    (void) pvParameters;
    int command; //0 hva, 1 light, 2 security
    int value;
    hva_message h;
    security_message s;
    lighting_message l;

    for(;;){
        command = rand() %3;

        if (command == 0){
            value = rand () %30 +10; //value of temperature to set from 10 to 29
            h.value = value;
            if(xQueueSend(hva_queue,&h,portMAX_DELAY)==pdPASS){
                //UART_printf("message sent correctly");
            }
            else{
                //UART_printf("ERROR: queue full\n");
            }
        }

        else if (command == 1){
            l.value = rand() %2; //turn the light
            if(xQueueSend(lighting_queue,&l,portMAX_DELAY)==pdPASS){
                //UART_printf("message sent correctly");
            }
            else{
                //UART_printf("ERROR: queue full");
            }
        }

        else{
            s.value = rand() %2; //Lock/unlock doors
            if(xQueueSend(security_queue,&s,portMAX_DELAY)==pdPASS){
                //UART_printf("message sent correctly");
            }
            else{
                //UART_printf("ERROR: queue full");
            }
        }

        vTaskDelay(1000);
    }

}



void logger_system(void *pvParameters){

    (void) pvParameters;

    while (1){
        UART_printf("No problem relevatad\n");
        vTaskDelay(20000);
    }
}
