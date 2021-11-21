Multisort algorithm, performance of its implementation for different values ​​of elements 'N' and different number of threads


Executions were performed for table sizes 16384 and 65535 and threads 1,2,4,8,16,32 and 64, as in the previous exercise. The results of the measurements are shown in the following graphs and tables.

+---------+----------+----------+----------+----------+
| Threads |  Run #1  |  Run #2  |  Run #3  | Average  |
+---------+----------+----------+----------+----------+
|       1 | 0.014588 | 0.013946 | 0.013474 | 0.014003 |
|       2 | 0.009429 | 0.012097 | 0.009900 | 0.010475 |
|       4 | 0.009460 | 0.007695 | 0.007079 | 0.008078 |
|       8 | 0.010019 | 0.007622 | 0.008914 | 0.008852 |
|      16 | 0.010969 | 0.012583 | 0.012851 | 0.012134 |
|      32 | 0.010361 | 0.015202 | 0.010615 | 0.012059 |
|      64 | 0.015166 | 0.022166 | 0.012965 | 0.016766 |
+---------+----------+----------+----------+----------+

Α = 16384


+---------+----------+----------+----------+----------+
| Threads |  Run #1  |  Run #2  |  Run #3  | Average  |
+---------+----------+----------+----------+----------+
|       1 | 0.032249 | 0.033827 | 0.042478 | 0.036185 |
|       2 | 0.026785 | 0.029562 | 0.036663 | 0.031003 |
|       4 | 0.063616 | 0.042038 | 0.061143 | 0.055599 |
|       8 | 0.055039 | 0.051750 | 0.057788 | 0.054859 |
|      16 | 0.050914 | 0.051380 | 0.064665 | 0.055653 |
|      32 | 0.033323 | 0.052057 | 0.032110 | 0.039163 |
|      64 | 0.039731 | 0.029584 | 0.027900 | 0.032405 |
+---------+----------+----------+----------+----------+



Α = 65536


We notice that regardless of the size of the data, we only have an improvement in execution time of up to 16 threads. From there on the performance drops and in fact for t = 64 threads it becomes worse than the execution in 1 thread. For larger volumes of data, increasing the threads increases the performance of the algorithm.










