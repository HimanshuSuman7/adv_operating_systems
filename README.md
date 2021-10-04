# Advanced Operating Systems Coursework

Assignments:

1. Write a program to create a process tree as shown in Figure #1. The input value through command line includes how many children a process has to spawn if process id is odd and if the process id is even. The third argument specifies the level of the tree. Figure shows the resultant tree if the command line argument is 2 (even pid), 1 (odd pid), and 3(level). Print the process identifiers in in-order traversal form. The program should create simultaneously executing processes in the same level as quickly as possible before child’s execution starts. Each process should print its process identifier and its parent process identifier by using the function getpid( ) and getppid( ) respectively. Your program should not create an orphan process while execution. The parent process should also print the exit status of its child processes. Output of a run: ./question1 1 2 3
