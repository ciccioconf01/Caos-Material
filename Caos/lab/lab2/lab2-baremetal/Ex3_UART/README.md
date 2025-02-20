# UART/USART DRIVER

The UART/USART (Universal Asynchronous/Synchronous Receiver/Transmitter) is a serial communication
peripheral that allows you to send and receive data. The UART peripheral is widely used in embedded
systems to communicate with other devices, such as a computer or a microcontroller. In our case, we
can use it to send data from our emulated ARM board in QEMU to our host computer. This is helpful
because it allows us to print messages in to our terminal. This is useful for debugging or seeing
the output of our program. 

In this exercise, we will implement a a Simple USART driver for sending messages from the QEMU ARM
board to the host computer. 

## UART/USART Basics
- UART is a serial communication protocol that uses two wires to transmit data: one for sending
  data (TX) and one for receiving data (RX).
- UART is asynchronous, meaning that there is no clock signal to synchronize the sender and
  receiver. Instead, the sender and receiver agree on a baud rate, which determines the speed at
  which data is transmitted.
- UART uses start and stop bits to frame each byte of data. The start bit signals the beginning of a
  byte, and the stop bit signals the end of a byte.
- UART is a full-duplex protocol, meaning that data can be transmitted in both directions
- USART is an extension of UART that adds support for synchronous communication. In synchronous
  mode, the sender and receiver use a shared clock signal to synchronize data transmission.

## How UART/USART Works
- The UART peripheral has a transmit buffer and a receive buffer. When you write data to the transmit
  buffer, the UART peripheral sends the data over the TX wire. When the UART peripheral receives data
  on the RX wire, it stores the data in the receive buffer.
- The UART peripheral has a status register that contains flags indicating whether the transmit buffer
  is empty, the receive buffer is full, and other status information.
- To send data using the UART peripheral, you write data to the transmit buffer and wait for the transmit
  buffer to become empty. To receive data, you read data from the receive buffer and wait for the receive
  buffer to become full.
- The UART peripheral sets a flag in the status register when the transmit buffer is empty or the
  receive buffer is full. You can check this flag to determine when it is safe to write or read
  data. 

## Implementing a Simple USART Driver
- To implent a simple driver we need to map the UART/USART registers to memory addresses in our C
  code. We can do this by defining a struct that represents the UART/USART registers and then
  casting the base address of the UART/USART peripheral to a pointer to this struct.
- The base address of the USART you can find it in the documentation attached to the exercise (Page
  50) and look for the USART1 peripheral.
- Your struct should contain the following fields:
  - `data_reg`: The data register where you write data to be transmitted.
  - `status_reg`: The status register that contains flags indicating the status of the USART peripheral.

- The order of the fields in the struct should match the order of the registers in the USART
  peripheral and the size of the fields should match the size of the registers (Check page 653 of
  the documentation).

- To implement a simple USART driver, we need to write the following functions:
- `static uint32_t usart_is_tx_ready(void);` This function will check the status register to see if the
  transmit buffer is empty. If the transmit buffer is empty, the function will return 1; otherwise, it
  will return 0.
- `uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes)` This function will write
  the specified number of bytes to the transmit buffer.
- It is important to note that the UART peripheral has physical buffers that store the data to be
  transmitted. That is why it is important to specify the number of bytes to be transmitted.

## Requirements of Function: `usart_tx_start(data_bytes, n_bytes)`
Transmits data over USART.

### Inputs:
- `data_bytes`: A pointer to the array of bytes to be transmitted.
- `n_bytes`: The total number of bytes to transmit.

### Outputs:
- `USART_TX_ERROR`: Error code indicating that no data was provided.
- `USART_TX_BUSY`: Error code indicating that transmission is busy or timed out.
- `USART_TX_INCOMPLETE`: Error code indicating that transmission was incomplete due to an early null-terminator.
- `USART_TX_COMPLETE`: Success code indicating that the data was transmitted successfully.

(Note: You can use an enum to define these error codes.)

### Pseudocode:
1. **Check for null pointer:**
   - If `data_bytes` is `NULL`, return `USART_TX_ERROR` (no data to transmit).
   
2. **Loop through each byte in `data_bytes`:**
   - **For each byte untl `n_bytes`:**
     - **Wait until USART transmit buffer is ready:**
         - **If `timeout` reaches 0**: 
           - Return `USART_TX_BUSY` (transmit buffer is still not ready).
       
     - **Transmit the current byte:**
       - Write the current byte (`*data_bytes`) to the USART data register (`usart1_t->data_reg`).
     
     - **Check for early null-terminator:**
       - If the next byte in the sequence is a null-terminator (`\0`) **and** not all bytes have
         been transmitted (i.e., `i < n_bytes - 1`), return `USART_TX_INCOMPLETE`.
       
3. **Return success:**
   - If all bytes have been successfully transmitted, return `USART_TX_COMPLETE`.

### Constants:
- `USART_TX_ERROR`: Error code for null input.
- `USART_TX_BUSY`: Error code for timeout or busy state.
- `USART_TX_INCOMPLETE`: Error code for incomplete transmission due to early termination.
- `USART_TX_COMPLETE`: Code for successful transmission.
- `TIMEOUT`: Constant for the maximum time to wait for the transmit buffer to be ready.

## Requirements of Function: `usart_is_tx_ready()`
Checks if the USART transmit buffer is ready for the next byte to be sent.

### Outputs:
- `1`: Indicates that the transmit buffer is empty and ready for the next byte.
- `0`: Indicates that the transmit buffer is not ready yet.

### Pseudocode:
1. **Check status register for buffer readiness**:
3. **Return `1` if the buffer is ready, or `0` if it is not.**
   
### Tips:
- `status_reg`: The register that contains the current status of the USART peripheral.
- `(1 << 7)`: A bit mask to isolate bit 7, which indicates whether the transmit buffer is ready (1 means ready, 0 means not ready).

- Now create a simple main function that uses the USART driver to send different messages to the host
computer. You can use the previous Delay function to add a delay between each byte transmission. 

- [Home](/README.md)
