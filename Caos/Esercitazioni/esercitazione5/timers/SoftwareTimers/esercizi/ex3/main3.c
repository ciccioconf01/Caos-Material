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

TimerHandle_t timer;
QueueHandle_t queue;
SemaphoreHandle_t mutex;

typedef struct{
    int temperature_value;  //value, -1 no value
    int alarm_value;        //0 no alarm, 1 alarm, -1 no value
}message;

//critical variables
int temperature; //value
int alarm; //0 no set, 1 set

void handler(){
    int number = rand()%2;
    message m;
    if(number==0){ //0 temperature , 1 alarm
        m.temperature_value = rand() %30 +10;
        m.alarm_value=-1;
        if(xQueueSend(queue,&m,portMAX_DELAY)==pdPASS){
            //UART_printf("message sent\n");
        }
        else{
            //UART_printf("error");
        }
    }

    else{

        m.temperature_value = -1;
        m.alarm_value=rand()%2;
        if(xQueueSend(queue,&m,portMAX_DELAY)==pdPASS){
            //UART_printf("message sent\n");
        }
        else{
            //UART_printf("error");
        }

    }
}

void task_lettura(void *pvParameters);
void task_scrittura(void *pvParameters);


int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    mutex = xSemaphoreCreateMutex();
    queue = xQueueCreate(10,sizeof(message));
    xTaskCreate(task_lettura, "task_lettura", 1000, NULL, mainTASK_PRIORITY+1, NULL);
    xTaskCreate(task_scrittura, "task_scrittura", 1000, NULL, mainTASK_PRIORITY+2, NULL);

    timer = xTimerCreate("timer",pdMS_TO_TICKS(2000),pdTRUE,(void *)0,handler);
    if(timer != NULL){
        xTimerStart(timer,0);
    }
    else{
        UART_printf("timer error");
    }
    

    vTaskStartScheduler();
    while (1);
}

void task_lettura(void *pvParameters){
    (void) pvParameters;
    char message1[20];
    char message2[20];
    while(1){
        xSemaphoreTake(mutex, portMAX_DELAY);
        
        UART_printf("CURRENT VALUES:\n");
        sprintf(message1,"Temperature: %d\n",temperature);
        if(alarm==0){
            sprintf(message2,"State Unlocked\n");
        }
        else{
            sprintf(message2,"State Locked\n");
        }
        
        UART_printf(message1);
        UART_printf(message2);
        xSemaphoreGive(mutex);

        vTaskDelay(4000);
    }
}

void task_scrittura(void *pvParameters){
    (void) pvParameters;
    message m;

    while(1){
        if(xQueueReceive(queue,&m,portMAX_DELAY)==pdPASS){
            //UART_printf("message received");
            xSemaphoreTake(mutex, portMAX_DELAY);
            if (m.temperature_value==-1){
                UART_printf("security message is arrived\n");
                alarm = m.alarm_value;
            }
            else{
                UART_printf("temperature message is arrived\n");
                temperature = m.temperature_value;
            }
            xSemaphoreGive(mutex);
        }
        else{
            UART_printf("error");
        }

        vTaskDelay(2000);
    }
    
}