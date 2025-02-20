# Exercise 3 - Memory

You have an embedded system that allocates memory with contiguous partitions using the best-fit strategy.
The system has **1000 MB of total memory**, divided into the following blocks:

| Block No. | Size (MB) | Status        |
|-----------|-----------|---------------|
| Block 1   | 150       | Allocated     |
| Block 2   | 300       | Free          |
| Block 3   | 200       | Allocated     |
| Block 4   | 50        | Free          |
| Block 5   | 100       | Free          |
| Block 6   | 200       | Allocated     |

The tasks running perform the following sequence of memory requests to be allocated using the **Best Fit strategy**:

1. Request 1: 40 MB  
2. Request 2: 70 MB  
3. Request 3: 120 MB  
4. Request 4: 60 MB  
5. Request 5: 80 MB  

Draw the memory layout after each allocation request. If a request cannot be allocated, mark it as **unallocated**.

After processing all requests, calculate the **external fragmentation**.
