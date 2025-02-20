#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//------------------
#include "uart.h"
#include <stdio.h> 
//------------------

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void soil_moisture_sensor(void *pvParameters);
void water_pump_controller(void *pvParameters);
void weather_forecast_system(void *pvParameters);
void logger_system(void *pvParameters);

QueueHandle_t sensorQueue;
QueueHandle_t weatherQueue;

typedef struct {
    int id;
    int hour;
    int minute;
    int level; //0 too dry, 1 accettable
}sensor_reading;

typedef struct {
    int rain //0 no rain predicted, 1 rain predicted
}weather_message;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    sensorQueue = xQueueCreate(10, sizeof(sensor_reading));
    weatherQueue = xQueueCreate(10,sizeof(weather_message));

    xTaskCreate(soil_moisture_sensor,"soil_moisture_sensor",1000,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(water_pump_controller,"water_pump_controller",1000,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(weather_forecast_system,"weather_forecast_system",1000,NULL,mainTASK_PRIORITY,NULL);
    xTaskCreate(logger_system,"logger_system",1000,NULL,mainTASK_PRIORITY,NULL);

    UART_init();

    /* your code goes here */
    // sample
    //xTaskCreate(OrderPickerTask, "OrderPicker", 1000, NULL, mainTASK_PRIORITY+1, NULL);

    vTaskStartScheduler();
    while (1);

}

void water_pump_controller(void *pvParameters){
    (void) pvParameters;

    weather_message w;
    sensor_reading s;

    int count;

    for(;;){

        if(xQueueReceive(sensorQueue,&s,portMAX_DELAY)==pdPASS){
            //UART_printf("correct reading");

            if (s.level == 0){ //too dry
                count = uxQueueMessagesWaiting(weatherQueue);

                if (count==0){
                    UART_printf("Activation of Water Pump\n");
                }

                else{
                    if(xQueueReceive(weatherQueue,&w,portMAX_DELAY)){
                        //UART_printf("correct reading");
                        if (w.rain == 1){
                            UART_printf("No need to activate water pump, will raing early\n");

                        }
                        else{
                            UART_printf("Activation of Water Pump\n");
 
                        }
                    }
                    else{
                        //UART_printf("error during reading");
                    }
                }



            }
        }

        else{
            //UART_printf("error during reading");
        }

    }

}

void weather_forecast_system(void *pvParameters){
    (void) pvParameters;
    weather_message w;

    for(;;){
        w.rain = rand() %2;
        if (w.rain == 1){
            if(xQueueSend(weatherQueue, &w, portMAX_DELAY)==pdPASS){
                //UART_printf("message sent correctly");
            }
            else{
                //UART_printf("Error: queue full");
            }
        }

        vTaskDelay(2000);
    }


}

void soil_moisture_sensor(void *pvParameters){
    (void) pvParameters;
    int index=0;
    sensor_reading s;

    for(;;){
        s.id=index;
        index++;
        s.hour = rand() %60;
        s.minute = rand() %60;
        s.level = rand() %2;

        if(xQueueSend(sensorQueue,&s,portMAX_DELAY)==pdPASS){
            //UART_printf("message sent correctly");
        }
        else{
            //UART_printf("ERROR, queue full");
        }

        vTaskDelay(400);
    }

}

void logger_system(void *pvParameters){
    (void) pvParameters;

    while(1){
        UART_printf("No problem");
        vTaskDelay(10000);
    }
}
