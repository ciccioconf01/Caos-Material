# Lab 4 - Queues mutexes and semaphores
In this lab, we'll see how to use the synchronization primitive (queues mutexes and semaphores) available in the FreeRTOS kernel. To synchronize the execution of different tasks.

To clone this repository, use the following command:
```
git clone --recurse-submodules
https://baltig.polito.it/teaching-material/labs-caos-and-os/lab4-synch.git
```
## Ex 1 - Queues
Queues are primitive for intertask communications. They can be used to exchange information or
data between different tasks, using an `Asynchronous` model of communications based on a `FIFO` (First
In First Out). They are bidirectional, which means that data can be written in both the head and tail
of the queue. 

All the items are passed by value, meaning the data (which can be a pointer to larger buffers) is
copied into the queue rather than the queue storing just a reference to the data. 
The access can be blocking or non-blocking; thanks to this, the Queues can also be used as a
synchronization primitive.

The classical scenario is the case of the producer and the consumer, in which one task is in charge
of creating/producing some data, and the other task needs to wait for that data and use it.

In FreeRTOS, Queue API functions permit a specified block time. When a task attempts to read
from an empty queue, the task will be placed into the Blocked state (so it is not consuming any CPU
time and other tasks can run) until either data becomes available on the queue or the block time
expires.


When a task attempts to write to a full queue, the task will be placed into the Blocked state (so is not consuming any CPU time, and other tasks can run) until either space becomes available in the
queue or the block time expires.

Before starting coding, the first step is to add the `queue.c` file into the `SOURCE_FILES` variables
in the Makefile at line 92; in this way, it'll be compiled and included in the .elf file.
```
SOURCE_FILES += $(KERNEL_DIR)/queue.c 
```
In this file are defined all the functions from FreeRTOS for working with the queues, the
documentation for using these functions can be found
[here](https://freertos.org/Documentation/02-Kernel/04-API-references/06-Queues/00-QueueManagement).

Now, starting from the `main.c`, to make the queue functions usable, we need to include the header
file:
```
#include "queue.h"
```
Create two tasks able to exchange numbers with a queue; the first task is the sender (producer) in
charge of generating `N=100` int between 0 to 999 randomly and sending them through the queue to the
receiver (consumer) that checks if the number is a multiple of seven and increase a counter. For both
tasks, every time an integer is written in the queue or red from the queue, a message is printed.

To use the Queue, use the following functions:
- `QueueHandle_t xQueueCreate( UBaseType_t length, UBaseType_t size)` to create a new queue and
 return the handler. Length is the number of items the Queue can hold; instead, the size is the
 number of bytes required to hold each item.
- `BaseType_t xQueueSend(
 QueueHandle_t handler,
 const void * pvItemToQueue,
 TickType_t TicksToWait )` to post an item on a queue. The item is queued by copy, not by reference. Where pvItemToQueue is a pointer to the item, and TicksToWait is the maximum amount of time the task should block waiting for space to become available on the Queue.
- `BaseType_t xQueueReceive(
 QueueHandle_t handler,
 void* pvBuffer,
 TickType_t TicksToWait
)` receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided. Where pvBuffer is the pointer to the buffer and TicksToWait the maximum amount of time the task should block waiting for an item to receive should the Queue be empty at the time of the call.                           
In both functions, the parameter TicksToWait can be set at the value of the global variable
`portMAX_DELAY`. 
   
Try now to add a `vTaskDelay` of 1 second in the sender's loop and report the differences with respect to before. Try to explain why this happened.

Now try to modify the number of TicksToWait in the sender function and set it to 0; explain now the
behavior.

### Tips
Since the print() function is not available to print a formatted string and our `UART_printf`
function despite the name not implementing any formation, the suggestion is to use  `sprint` or `snprintf` to format a string and then use our UART_printf, writing the string already formatted.



## Ex 2.1 - Mutexes
In real-time systems, multiple tasks often need access to shared resources like data structures, hardware peripherals, or memory buffers. Without proper control, this can lead to data inconsistency or race conditions. To manage access and prevent conflicts, FreeRTOS provides mutexes and semaphores, which are two synchronization mechanisms.

### Mutex (Mutual Exclusion)
A mutex is used for exclusive access to a resource, ensuring that only one task can access a critical section at a time. In FreeRTOS, mutexes also support priority inheritance, which helps prevent priority inversion, a common issue in multitasking systems.

### Semaphore
A semaphore can be thought of as a counter that controls access to a shared resource. FreeRTOS supports both binary semaphores (which are similar to mutexes but without ownership restrictions) and counting semaphores (which allow multiple tasks to access a resource up to a certain limit).

FreeRTOS Mutex and Semaphore APIs
Below are some key FreeRTOS APIs for working with mutexes and semaphores. [Info](https://www.freertos.org/Documentation/02-Kernel/04-API-references/10-Semaphore-and-Mutexes/06-xSemaphoreCreateMutex).

1. Creating a Mutex
`SemaphoreHandle_t xMutex = xSemaphoreCreateMutex()`
Description: Creates a mutex and returns a handle to it. If the mutex cannot be created, NULL is returned.

2. Taking (Locking) a Mutex
`xSemaphoreTake(xMutex, xTicksToWait)`
Description: Attempts to lock (take) the mutex. The task will block if the mutex is not available, until it either becomes available or xTicksToWait time has passed.
- Parameters:
    - xMutex: The mutex handle.
    - xTicksToWait: Maximum wait time in ticks. Use portMAX_DELAY to wait indefinitely.
Returns: pdTRUE if the mutex was taken successfully, pdFALSE otherwise.

3. Giving (Releasing) a Mutex
`xSemaphoreGive(xMutex)`
Description: Releases the mutex, making it available to other tasks.
- Parameters: 
    - xMutex - The mutex handle.
### Note: Only the task that locked the mutex can unlock it, ensuring mutual exclusion.

Exercise: Implement two tasks that attempt to access a shared resource. Use a mutex to ensure that only one task at a time can access the resource, preventing race conditions.

Instructions: 
- In Task 1, attempt to lock the mutex using xSemaphoreTake(). Once the mutex is locked, print a message indicating that Task 1 is accessing the shared resource. Simulate work by delaying the task. Release the mutex using xSemaphoreGive() after completing the critical section.
- In Task 2, follow a similar process as Task 1: attempt to lock the mutex, print a message, simulate work, and release the mutex.

## Ex 2.2 - Binary Semaphores
In this exercise, you will implement a logging system in FreeRTOS using binary semaphores to ensure that multiple tasks can log messages without interfering with each other.

Instructions:
- Create a global buffer to hold log messages. You will also need a variable to keep track of the index for the next log entry.
- Use the FreeRTOS API to create a binary semaphore that will manage access to the logging system. This will ensure that only one task can log a message at any given time.
- Create a task function that will generate log messages. The task should:
    - Attempt to take the binary semaphore before logging.
    - Log a message to the buffer.
    - Release the semaphore after logging.
- Introduce a delay between log messages to simulate different logging intervals. Use vTaskDelay() to achieve this.

## Ex 2.3 - Counting Semaphores
In this exercise, you will implement an  producer-consumer scenario using counting semaphores in FreeRTOS. The producer will generate random items and add them to a buffer, while the consumer will retrieve and process these items. The counting semaphores will manage the synchronization between the producer and consumer tasks.

Instructions: 
- Create a circular buffer that can hold a specified number of items, along with indices for the producer and consumer.
- Create two counting semaphores: one for tracking the number of empty slots in the buffer and another for tracking the number of filled items. Initialize the empty slots semaphore to the size of the buffer and the filled items semaphore to zero.
- Implement the Producer Task:
    - Generate a random item (e.g., a number).
    - Wait for an empty slot by taking the empty slots semaphore.
    - Add the item to the buffer.
    - Signal that an item is available for consumption by giving the filled items semaphore.
    - Introduce a random delay to simulate different production times.
- Implement the Consumer Task:
    - Wait for an available item by taking the filled items semaphore.
    - Retrieve the item from the buffer.
    - Process the item (for instance, printing it).
    - Signal that a slot is free by giving the empty slots semaphore.
    - Introduce a random delay to simulate different consumption times.

