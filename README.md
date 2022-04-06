# CP384A04
This assignment is based on the concept of deadlock avoidance and contiguous memory allocation.
# CP386-Assignment4

**DEADLOCK AVOIDANCE(Question1)  AND CONTAGIOUS MEMORY ALLOCATION(Question2)**

This assignment is based on the concept of deadlock avoidance and contiguous memory allocation.


**RUNNING QUESTION 1 DESCRIPTION (BY Yvonne I.)**


**RUNNING QUESTION 2 DESCRIPTION ( BY Yvonne I.)**
This program shows how orcesses are allocated momory through contiguous memory allocation is done using linked list.

Thes program must respond to three different requests:
* Request for a contiguous block of memory
* Release of a contiguous block of memory
* Report the regions of free and allocated memory


The program then is passed the initial amount of memory to start with for example 1000000 bytes

**./Question2 1000000**

Once started it will display a command prompt as shown below;

**command>**

The user then is to enter the command in the below format;

**RQ (process number) (size) (B)**

‘RQ’ command is the new process that requires the memory, followed by the amount of memory being requested, and finally the algorithm. (In this program, “B” refers to best fit.) For example;

**command>RQ P0 200000 B**

The above commands allocates a 200000kb to process P0

**command>RL P0**
The above command reales a the memory for process P0

**command>Status**
The above command displays the status information of the memory

**Screenshots**



<img width="279" alt="image" src="https://user-images.githubusercontent.com/68035004/161671876-ea5a0c41-9abb-4f98-8e46-f53a125c592d.png">

**Individual Contributions (All by Yvonne)**

**Features**
The system has function such as;

best_fit()
request_memory()
releasememory()
memory_status()
input_check()
main()

**Makefiles**
Question2_makefile- file is the make file

**Test Cases**

The user has to enter the below commands as test cases and get the information inform of outputs
command>RQ P0 200000 B
command>RL P0
command>Status

**Commit History**

**First Commit**
* Repository Created 
* README.md file created

**Second Commit**
* README.md file updated


**Author (About Developers)**
1. Yvonne Itangishaka- https://github.com/yvonneitan


**License**

* This project is licensed under MIT License. Please reffer from LICENSE.md file for more details.






