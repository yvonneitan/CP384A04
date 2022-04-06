Run Question1 and Question2:

Open your command Terminal and enter the below commands to run the tasks separately 

CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
Question1: Question1.c
	$(CC) $(CFLAGS) -o Question1 Question1.c $(LDFLAGS)
Question2: Question2.c
	$(CC) Question2.c -o Question2

runq3: Question1
	./Question1 10 7 5 8 
runq2: Question2
	./Question1 1000000
