#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//------------------
#include "uart.h"
#include <stdio.h> 
//------------------

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
void vehicle_detection_system (void *pvParameters);
void traffic_light_controller (void *pvParameters);
void congestion_monitor (void *pvParameters);
void logger_system (void *pvParameters);
void smph (void *pvParameters);

QueueHandle_t vehicle_queue;
QueueHandle_t trafficLightQueue;


typedef struct{
    int id;
    int hour;
    int minute;
    int priority; //0 low priority, 1 high priority
} vehicle;

typedef struct{
    int light; //0 red; //1 green
}message;




int sem; //0 red; 1 green; 2 yellow


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    trafficLightQueue = xQueueCreate(10, sizeof(message));
    vehicle_queue = xQueueCreate(10, sizeof(vehicle));

    if (trafficLightQueue == NULL || vehicle_queue == NULL){
        UART_printf("Error queues");
    }

    UART_init();
    xTaskCreate(vehicle_detection_system, "vehicle_detection_system",1000,NULL,mainTASK_PRIORITY+1,NULL);
    xTaskCreate(traffic_light_controller, "traffic_light_controller",1000,NULL,mainTASK_PRIORITY+2,NULL);
    xTaskCreate(congestion_monitor, "congestion_monitor",1000,NULL,mainTASK_PRIORITY+2,NULL);
    xTaskCreate(logger_system, "logger_system",1000,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(smph, "semaphore",1000,NULL,mainTASK_PRIORITY+2,NULL);


    vTaskStartScheduler();
    while (1);
}

void smph (void *pvParameters){
    (void) pvParameters;

    int messageCount;

    message m;

    for(;;){
        UART_printf("GREEN\n");
        sem = 1;
        vTaskDelay(1000);

        UART_printf("YELLOW\n");
        sem=2;
        vTaskDelay(250);

        UART_printf("RED\n");
        sem = 0;
        vTaskDelay(250);

        messageCount = uxQueueMessagesWaiting(trafficLightQueue);

        if (messageCount != 0){
            if (xQueueReceive(trafficLightQueue,&m,portMAX_DELAY)==pdPASS){
                if (m.light==1){
                    UART_printf("GREEN\n");
                    sem = 1;
                    vTaskDelay(500);

                    UART_printf("YELLOW\n");
                    sem=2;
                    vTaskDelay(500);

                    UART_printf("RED\n");
                    sem = 0;
                    vTaskDelay(250);
                }
                else{
                    vTaskDelay(250);
                }
            }

            else{
                UART_printf("ERROR2");
            }
        }

        else{
            vTaskDelay(250);
        }
        

        
    }
}


void vehicle_detection_system (void *pvParameters){
    (void) pvParameters;

    int index = 0;
    vehicle v;
    for (;;){
        v.id = index;
        index++;
        v.minute = rand() %60;
        v.hour = rand() %60;
        v.priority = rand()%2;

        if (xQueueSend(vehicle_queue,&v,portMAX_DELAY)==pdPASS){
            //UART_printf("veichle inserted in queue");
        }
        else{
            UART_printf("ERROR: queue full\n");

        }
    }

    vTaskDelay(500);
}

void traffic_light_controller (void *pvParameters){

    (void) pvParameters;
     
    vehicle v;
    message m;

    for (;;){


        if(xQueueReceive(vehicle_queue,&v,portMAX_DELAY)==pdPASS){
        
            if (v.priority == 1){
                m.light = 1;

                if (xQueueSend(trafficLightQueue,&m,portMAX_DELAY)==pdPASS){
                    //UART_printf("message sent");
                }
                else{
                    UART_printf("ERROR: traffic Light Queue full\n");
                }
            }


        }
        vTaskDelay(rand()%1500);
    }

    
}

void congestion_monitor (void *pvParameters){
    (void) pvParameters;

    message m;
    int vehicleCount;
    int limit = 4;

    for(;;){

        vehicleCount = uxQueueMessagesWaiting(vehicle_queue);
        if (vehicleCount > limit){
            m.light = 1;

            if(xQueueSend(trafficLightQueue,&m,portMAX_DELAY)==pdPASS){
                //UART_printf("message sent correctly");
            }
            else{
                UART_printf("ERROR\n");            }
        }

        
        vTaskDelay(rand()%1500);

    }
}

void logger_system(void *pvParameters){
    
    (void) pvParameters;

    for(;;){
        //UART_printf("No problems detected");
        vTaskDelay(5000);
    }
}


