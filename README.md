# CP384A04
This assignment is based on the concept of deadlock avoidance and contiguous memory allocation.
# CP386-Assignment4

**DEADLOCK AVOIDANCE(Question1)  AND CONTAGIOUS MEMORY ALLOCATION(Question2)**

This assignment is based on the concept of deadlock avoidance and contiguous memory allocation.


**QUESTION 1 DESCRIPTION AND RUNNING (BY Yvonne I.)**

This program shows deadlock management using Banker's Algorithm.

The program consider requests from n customers for m resource types.

The banker keeps track of the resources using the following data structures:
* the available amount of each resource
* the maximum demand of each customer
* the amount currently allocated to each customer
* the remaining need of each customer

The program then is passed the a sample file with a matrix of resources


**./Question1 10 5 7 8**

**EXAMPLES**

If customer/thread 0 were to request the resources (1, 0, 0, 1), the following command would be entered:

**RQ 0 1 0 0 1**

If customer 4 wishes to release the resources (1, 0, 0, 0), the user would enter the following command:

**RL 4 1 0 0 0**


When the command **‘Status’** is excecuted ,the program would output; 

* the current state of the available, 
* the maximum array 
* the allocation array
* the need arrays

Whe command ‘Run’ would executes the program would;

* run the safe sequence based on the current state and all the customers (threads) 
* then the following prints for each thread:

* The safe sequence
*  Name of thread running in sequence ordering
* Allocated Resources
* Need
* Available resources
* A message: “Thread has started”
* A message: “Thread has finished”
* A message: “Thread is releasing resources”
* New Available status

**Features**

The program has functions;

* int readInput()
* int readFile()
* int isSafe()
* void resources_stat()
* int bankersAlgo()
* void* customer(void *t)

**TEST**

osc@ubuntu:~/A04/bankers-algorithm$ ./Question1 10 5 7 8 

Number of Customers: 5 

Currently Available resources: 

10 5 7 8 

Maximum resources from file: 

6 4 7 3 

4 2 3 2

2 5 3 3

6 3 3 2

5 5 7 5 

Enter Command: RQ 0 1 0 0 1 

State is safe, and request is satisfied 

Enter Command: RQ 1 1 1 1 1 

State is safe, and request is satisfied 

Enter Command:


**SCREENSHOT**

<img width="337" alt="Screen Shot 2022-04-06 at 8 40 59 AM" src="https://user-images.githubusercontent.com/68035004/161976802-bb3c7d51-5e67-4fa1-965a-d1bb8b4a9c39.png">





**QUESTION 2 DESCRIPTION AND RUNNING ( BY Yvonne I.)**

This program shows how processes are allocated memory through contiguous memory allocation ( Best fit Algorithm) and is done using linked list.

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

**Features**
The system has function such as;

* best_fit()
* request_memory()
* releasememory()
* memory_status()
* input_check()
* main()

All these finctions work together to in requestiona and releasing memory in the process of allocation

**Test Cases**

The user has to enter the below commands as test cases and get the information inform of outputs
command>RQ P0 200000 B
command>RL P0
command>Status

$ ./Question2 1000000 

Allocated 1000000 bytes of memory 

command>RQ P0 200000 B 

Successfully allocated 200000 to process P0 

command>RQ P1 350000 B 

Successfully allocated 350000 to process P1 

command>RQ P2 300000 B 

Successfully allocated 300000 to process P2 

command>RL P0 

releasing memory for process P0 

Successfully released memory for process P0 

command>Status 

Partitions [Allocated memory = 650000]: 

Address [200000:549999] Process P1 

Address [550000:849999] Process P2 

Holes [Free memory = 350000]: 

Address [0:199999] len = 200000 

Address [850000:999999] len = 150000 

command>RQ P3 120000 B 

Successfully allocated 120000 to process P3 

command>Status Partitions [Allocated memory = 770000]: 

Address [200000:549999] Process P1 

Address [550000:849999] Process P2 

Address [850000:969999] Process P3 

Holes [Free memory = 230000]: 

Address [0:199999] len = 200000 

Address [970000:999999] len = 30000 

command>RQ P4 150000 B 

Successfully allocated 150000 to process P4 

command>RQ P5 80000 B 

No hole of sufficient size 

command>Status 

Partitions [Allocated memory = 920000]: 

Address [0:149999] Process P4 

Address [200000:549999] Process P1 

Address [550000:849999] Process P2 

Address [850000:969999] Process P3 


Holes [Free memory = 80000]: 

Address [150000:199999] len = 50000 

Address [970000:999999] len = 30000

**SCREENSHOTS**

<img width="448" alt="Screen Shot 2022-04-06 at 8 41 07 AM" src="https://user-images.githubusercontent.com/68035004/161977269-97d814da-bde7-495b-8755-3b47f56d5980.png">



**CONTRIBUTIONS**

* All work done alone


**MAKEFILES**
* Question1
* Question2


**COMMIT HISTORY**

**First Commit**
* Repository Created 
* README.md file created

**Second Commit**
* README.md file updated

**Third Commit**
* Question2.c added

**Fourth Commit**
* Question1.c added

**Fifth Commit**
* README.md updated on Question2 Description

**Sixth Commit**

* Makefile added
* Features added

**Seventh Commit**
 READDME.md done
 
**AUTHORS (About Developers)**
1. Yvonne Itangishaka- https://github.com/yvonneitan


**LICENCE**

* This project is licensed under MIT License. Please reffer from LICENSE.md file for more details.






