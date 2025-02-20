//function.h//

#ifndef functions_h
#define functions_h

#include <stdint.h>
#include <stddef.h>

#define USART1_BASE (0x40011000)


typedef struct {
    volatile uint32_t status_reg; // Registro di stato
    volatile uint32_t data_reg;   // Registro dati
} usart1_t;

#define usart ((usart1_t *) USART1_BASE)

enum message{
    USART_TX_ERROR,         //0 (no data provided)
    USART_TX_BUSY,          //1 (the transmission is busy or timed out)
    USART_TX_INCOMPLETE,    //2 (the trasmission is incomplite due to an early null-terminator)
    USART_TX_COMPLETE,      //3 (the trasmission is complete)

};


void usart_init(void);
uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
void delay_routine_1(void);
void delay_routine_2(unsigned int delay_counter);

#endif // functions.h