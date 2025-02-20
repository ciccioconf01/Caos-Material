Exercise 2 - FreeRTOS and Deferred Interrupt Handling

Create a FreeRTOS project using the mps2-an385 emulated board in QEMU and the basic skeleton provided in this folder.

The base project provides hardware support using the CMSIS Board Support Package. It includes implementations for the printf function and initializes the hardware timer TIMER1 available on the board for periodic interrupts.
System Requirements

The system must perform the following tasks:

    Computational Task (Task A):
        Execute a periodic task with a period of 40ms.
        Each time this task is activated, it computes the dot product of two 10-element vectors initialized with fixed values.
        This task emulates a computationally intensive operation.

    Interrupt Handling:
        Define an interrupt handler for TIMER1.
        Use the deferred interrupt handling technique to manage the interrupt in a FreeRTOS task.
        Every time the interrupt is triggered:
            Increment a counter to keep track of the number of interrupts served.
            Print a message from the deferred interrupt handler task indicating the total number of interrupts served.

    Monitoring Task (Task B):
        Create a separate monitoring task with a period of 100ms.
        The monitoring task prints the current value of the interrupt counter and the execution time of Task A.