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

The project should create the following tasks:

* `startup` it is the first task running with the highest priority in the system. Let's name this priority `MAX_PRIRITY`. This task must initialize a global variable named `count` to 0 and then create three additional tasks named `task1`, `task2`, `task3`. Finally the tasks ends.
* `task1`, `task2` have both priority equal to `MAX_PRIRITY-2`. They must run in parallel using round robin. They must perform an infinite loop. Every 10ms `task1` increments the variable `count` by 5, whereas `task2` increments `count` by 10. Both tasks print their name and the current value of `count` at each iteration.
* `task3`, has priority equal to `MAX_PRIRITY-1`. It must sleep for 1s leaving `task1`, `task2` free to run. It then wakes up prempting the CPU, prints its name on screen and starts an infinite busy waiting keeping the CPU busy.

**There is no need to protect the access to the shared variable with a semaphore**

**When you submit your exam only the App folder must be included in the ZIP.**

Refer to the FreeRTOS documentation here: [https://www.freertos.org/Documentation/00-Overview](https://www.freertos.org/Documentation/00-Overview)
