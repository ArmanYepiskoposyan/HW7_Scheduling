Homework 7: Process Scheduling Simulation

This program implements two CPU scheduling algorithms:
First Come First Served (FCFS) and Shortest Job First (SJF).

The user enters the number of processes, arrival times,
and burst times.

The program calculates the waiting time, turnaround time,
and response time for each process. It also displays the
average times and a Gantt chart showing the execution order.

Both algorithms are non-preemptive.


Compilation

To compile the program, use:

gcc -Wall -Wextra scheduling.c -o scheduling


Execution

To run the program, use:

./scheduling


Example Input

Number of processes: 4

Process 1: 0 8
Process 2: 1 4
Process 3: 2 9
Process 4: 3 5

The first number is the arrival time and the second
number is the burst time.


Algorithms

FCFS runs processes in the order they arrive.

SJF runs the shortest available process first.
If two processes have the same burst time, the one
that arrived earlier is selected.


Output

The program prints a Gantt chart for both algorithms.

It also displays the process ID, arrival time, burst time,
waiting time, turnaround time, and response time.

Finally, it prints the average waiting, turnaround,
and response times for each algorithm.
