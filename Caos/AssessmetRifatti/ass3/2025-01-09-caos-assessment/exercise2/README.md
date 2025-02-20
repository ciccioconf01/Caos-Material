# Exercise 2 — Memory Management

A computer system has a virtual memory with 64 KB (65,536 bytes) of addressable space and a page size of 4 KB (4,096 bytes). The physical memory can hold 4 pages at a time. The Second Chance algorithm is used as the page replacement policy.

Given the following sequence of virtual memory addresses:

* breafly describe the behaviour of the second chance algorithm
* calculate the corresponding page numbers 
* simulate the behaviour of the Second Chance algorithm step by step
* compute the total number of pages faults

Address reference sequence (in decimal):
1050, 8195, 16384, 24576, 8192, 12345, 8195, 16400, 24576, 12350, 8192, 12345, 24575

Initial Conditions:

* The memory starts empty.
* The reference bits for all pages are initially set to 0.
* The pointer starts at the first frame (Frame 0).

**N.B. If you write your solution on paper make sure it is readable.**

Stringa 0   2   4   6   2   3   2   4   6   3   2   3   5
Frame0  00  00  00  00  00  30  30  30  30  31  31  31  30             
Frame1      20  20  20  21  21  21  21  21  21  21  21  50
Frame2          40  40  40  40  40  41  41  41  41  41  40
Frame3              60  60  60  60  60  61  61  61  61  60
PF      X   X   X   X       X                           X

