# Exercise 4 - FreeRTOS tasks

Create a FreeRTOS project based on the template available here: [https://baltig.polito.it/teaching-material/exercises-caos-and-os/FreeRTOSsampleapp](https://baltig.polito.it/teaching-material/exercises-caos-and-os/FreeRTOSsampleapp).

```
├── App
│   ├── FreeRTOSConfig.h
│   ├── Makefile
│   ├── main.c
│   ├── mps2_m3.ld
│   ├── startup.c
│   ├── uart.c
│   └── uart.h
└── README.md
```

The project should create three tasks following tasks:

* TaskA and TaskB are low-priority periodic tasks with the same priority with a period of 500 msec. During each period, the task performs a loop that updates an integer shared variable 50 times and prints the variable value on the screen. Task A increments the variable, while Task B decrements the variable. The two tasks must run in a synchronized way (Task A first and then Task B). The synchronization must be guaranteed through semaphores.
* TaskC is a high-priority task that is activated by a software timer that fires every 700ms. This task must take the current value of the variable shared by TaskA and TaskB and must compute the factorial of the variable. The computation must be implemented using inline assembly code.

**When you submit your exam only the App folder must be included in the ZIP.**

Refer to the FreeRTOS documentation here: [https://www.freertos.org/Documentation/00-Overview](https://www.freertos.org/Documentation/00-Overview)
