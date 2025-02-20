//main.c//

#include "functions.h"

//extern uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
//extern uint32_t usart_is_tx_ready(void);
//extern void delay_routine_1(void);
//extern void delay_routine_2(unsigned int delay_counter);
//extern void usart_init(void);

int main(){
    
    usart_init();
    const uint8_t message_to_send[] = "Ciaone\n";
    usart_tx_start(message_to_send,sizeof(message_to_send)-1);

    while (1); // Mantieni il programma in esecuzione
    return 0; // Non dovrebbe mai raggiungere questa linea

}