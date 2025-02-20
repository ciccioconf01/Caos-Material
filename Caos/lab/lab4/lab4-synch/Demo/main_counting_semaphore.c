#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )
#define BUFFER_SIZE          5   // Dimensione del buffer circolare
#define N                    20  // Numero di operazioni da eseguire

// Dichiarazioni per i task
void vTaskFunction_Producer(void *pvParameters);
void vTaskFunction_Consumer(void *pvParameters);

// Buffer circolare e variabili per gestire i suoi indici
int buffer_circolare[BUFFER_SIZE];
int head = 0;
int tail = 0;

// Semafori per sincronizzazione
SemaphoreHandle_t xSemaphore_filled;
SemaphoreHandle_t xSemaphore_empty;

int main(int argc, char **argv){
    (void) argc;
    (void) argv;

    UART_init();  // Inizializza la UART per la stampa

    // Inizializza il buffer circolare a -1 (segno che è vuoto)
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer_circolare[i] = -1;
    }

    // Crea i semafori
    xSemaphore_filled = xSemaphoreCreateCounting(BUFFER_SIZE, 0);  // Inizialmente vuoto
    xSemaphore_empty = xSemaphoreCreateCounting(BUFFER_SIZE, BUFFER_SIZE);  // Inizialmente pieno

    if (xSemaphore_filled == NULL || xSemaphore_empty == NULL) {
        UART_printf("Errore nella creazione dei semafori\n");
        return 1;
    }

    // Crea i task produttore e consumatore
    xTaskCreate(vTaskFunction_Producer, "Task_Producer", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL);
    xTaskCreate(vTaskFunction_Consumer, "Task_Consumer", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL);

    // Avvia il piano di esecuzione (scheduler)
    vTaskStartScheduler();

    // Codice non raggiungibile se il sistema FreeRTOS funziona correttamente
    for (;;) {
        // Loop infinito (se qualcosa va storto, questo è il punto in cui finirà il codice)
    }

    return 0; // Questo non verrà mai raggiunto
}

/* Funzione del produttore */
void vTaskFunction_Producer(void *pvParameters) {
    (void) pvParameters;

    for (int i = 0; i < N; i++) {
        int random_number = (rand() % 1000) + 1;  // Genera un numero casuale

        // Aspetta che ci sia spazio disponibile nel buffer (xSemaphore_empty)
        xSemaphoreTake(xSemaphore_empty, portMAX_DELAY);

        // Scrive nel buffer circolare
        buffer_circolare[head] = random_number;
        head = (head + 1) % BUFFER_SIZE;  // Incrementa head circolarmente

        // Stampa il messaggio via UART
        char message[20];
        sprintf(message, "Producer wrote %d", random_number);
        UART_printf(message);
        UART_printf("\n");

        // Rilascia il semaforo per indicare che ci sono dati nel buffer (xSemaphore_filled)
        xSemaphoreGive(xSemaphore_filled);

        // Delay casuale tra 0 e 1000 ms
        vTaskDelay(pdMS_TO_TICKS(rand() % 1000));
    }
}

/* Funzione del consumatore */
void vTaskFunction_Consumer(void *pvParameters) {
    (void) pvParameters;

    for (int i = 0; i < N; i++) {
        // Aspetta che ci siano dati nel buffer (xSemaphore_filled)
        xSemaphoreTake(xSemaphore_filled, portMAX_DELAY);

        // Legge dal buffer circolare
        int number = buffer_circolare[tail];
        buffer_circolare[tail] = -1;  // Resetta la posizione del buffer

        tail = (tail + 1) % BUFFER_SIZE;  // Incrementa tail circolarmente

        // Stampa il messaggio via UART
        char message[20];
        sprintf(message, "Consumer read %d", number);
        UART_printf(message);
        UART_printf("\n");

        // Rilascia il semaforo per indicare che c'è spazio nel buffer (xSemaphore_empty)
        xSemaphoreGive(xSemaphore_empty);

        // Delay casuale tra 0 e 1000 ms
        vTaskDelay(pdMS_TO_TICKS(rand() % 1000));
    }
}
