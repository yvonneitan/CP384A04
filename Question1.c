



/*
 -------------------------------------
 Author:  Yvonne Itangishaka
 ID:      176753040
 Email:   itan3040@mylaurier.ca
 Github Name:https://github.com/yvonneitan/CP384A04
 Version  2022-04-05
 
 -------------------------------------
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <stdbool.h>
#define RESOURCES 10

struct matrix { // matrix dimensions.
	int rows;
	int columns;
} limit;

typedef struct thread { // representation of a single customer
	int thread_ID;
	int thread_state;
	int return_num;
	pthread_t thread_check;
} Thread;

//Banker's algorithm important items
pthread_mutex_t lock;
int allocation_matrix[RESOURCES][RESOURCES];
int max_matrix[RESOURCES][RESOURCES];
int available_matrix[RESOURCES];
int need_matrix[RESOURCES][RESOURCES];
int stored_resources[RESOURCES];
bool Finish[RESOURCES];

//declaration of the functions
int readInput(void);
int readFile(void);
int isSafe(void);
void resources_stat(void);
int bankersAlgo(void);
void* customer(void *t);

//Beginning of the program
int main(int argc, const char *argv[]) {

	int count_update;
	if (argc < 3) { // check if there are enough arguments
		printf("Please, Input enough items\n");
		return -1;
	} else {
		//store the values in a matrix
		for (count_update = 0; count_update < argc - 1; count_update++)
			available_matrix[count_update] = atoi(argv[count_update + 1]);

	}

	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("Failed\n");
		return 1;
	}

	printf("Number of customers is: %d \n", count_update + 1);
//	a call to the read file function to read the file txt
	readFile();
	printf("\n");

	printf("Currently available Resources:");
	for (int j = 0; j < limit.columns; j++) {
		printf("%d ", available_matrix[j]);
	}
	printf("\n");

	printf("Maximum Resources from file:\n");
	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			printf("%d ", max_matrix[i][j]);
		}
		printf("\n");
	}

	//a call to the input file function
	readInput();

//	This checks if the alg is safe
	if (isSafe() == 1) {
		return 0;
	}
	bankersAlgo(); //Banke'r algorythm
	pthread_mutex_destroy(&lock);
	return 0;
}

//reading file

int readFile() {
	int ch;
	int rows = 0;
	int columns = 0;
	FILE *file = fopen("sample4_in.txt", "r");
	if (file) {
		//persing through the file
		while ((ch = getc(file)) != EOF) {
			if (rows == 0 && ch == ',') {
				columns++;
			}
			if (ch == '\n') {
				rows++;
			}
		}
		columns++;
		rows++;
		limit.rows = rows;
		limit.columns = columns;
		fseek(file, 0, SEEK_SET);
		int i = 0; //represents rows
		int j = 0; //represents columns
		while ((ch = getc(file)) != EOF) {
			if (ch >= '0' && ch <= '9') {
				max_matrix[i][j] = ch - 48;
			} else if (ch == ',') {
				j++;
			} else if (ch == '\n') {
				i++;
				j = 0;
			}
		}
		fclose(file);
	}
	return 0;
}
//User inputs
int readInput() {
	for (int i = 0; i < RESOURCES; i++) {
		for (int j = 0; j < RESOURCES; j++) {
			allocation_matrix[i][j] = 0;
		}
	}
	bool check = true;
	while (check) {
		char string[RESOURCES + 3];
		char *test = string;
		printf("Enter a Command: ");
		scanf("%s", test);
		if (*test == '*') {
			check = false;
			resources_stat();
			//In case no resources print an error output
		} else if ((*(test + 2) - 48) >= limit.rows) {
			printf("Out of bounds!\n");
			//Requesting Resources
		} else if (*(test + 1) == 'Q') {
			int rows = *(test + 2) - 48;
			for (int i = 3; i < limit.columns + 3; i++) {
				allocation_matrix[rows][i - 3] += *(test + i) - 48;
			}

			//Releasing resources
		} else if (*(test + 1) == 'L') {
			int rows = *(test + 2) - 48;
			for (int i = 3; i < limit.columns + 3; i++) {
				allocation_matrix[rows][i - 3] -= *(test + i) - 48;
			}

		}

	}
	return 0;
}
//calculates the need_matrix matrix and then checks for safe thread_state
int isSafe() {
	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];
		}
	}
	printf("\n");

	printf("Needed Resources:\n");
	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			printf("%d ", need_matrix[i][j]);
		}
		printf("\n");
	}

	printf("Available Resources:\n");
	for (int j = 0; j < limit.columns; j++) {
		stored_resources[j] = available_matrix[j];
		printf("%d ", stored_resources[j]);
	}

	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			if (need_matrix[i][j] < 0) {
				printf("Not Safe!");
				return 1;
			}
		}
	}
	printf("\n");

	for (int j = 0; j < limit.columns; j++) {
		Finish[j] = false;
	}
	return 0;
}
void resources_stat() {

	printf("Maximum Resources:\n");
	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			printf("%d ", max_matrix[i][j]);
		}
		printf("\n");
	}

	printf("Allocated Resources:\n");
	for (int i = 0; i < limit.rows; i++) {
		for (int j = 0; j < limit.columns; j++) {
			printf("%d ", allocation_matrix[i][j]);
		}
		printf("\n");
	}

}

int bankersAlgo(void) { //runs bankers algorithm and finds safe sequence.
	printf("\nEnter a Command: Run\n");
	int count = 0; //count_update variable.
	bool checked; //checks if count updated.
	while (count < limit.rows) {
		for (int i = 0; i < limit.rows; i++) {
			checked = true;
			int j;
			for (j = 0; j < limit.columns && checked; j++) {
				if (!Finish[i]) {
					if (need_matrix[i][j] > stored_resources[j]) {
						checked = false;
					}
				} else {
					checked = false;
					break;
				}
			}
			if (checked) {
				Thread *thread = NULL;
				thread = (Thread*) malloc(sizeof(Thread));
				thread->thread_ID = i;
				thread->thread_state = 1;
				thread->return_num = pthread_create(&(thread->thread_check),
						NULL, customer, thread);
				sleep(2);
				Finish[i] = true;
				count++;

			}
		}
	}
	printf("\nEnter Command: Exit\n");
	return 0;
}
void logStart(int tID) {
	printf("\n\t Thread has started.");
}

void logFinish(int tID) {
	printf("\n\t Thread has finished.");
}

void* customer(void *t) //Thread function.
{
	pthread_mutex_lock(&lock);

	int i = ((Thread*) t)->thread_ID;
	printf("-->  Customer %d :\n", i);
	printf("\t Allocated Resources: ");
	for (int j = 0; j < limit.columns; j++) {
		printf("%d ", allocation_matrix[i][j]);
	}
	printf("\n");

	printf("\t Needed Resources: ");
	for (int j = 0; j < limit.columns; j++) {
		printf("%d ", need_matrix[i][j]);
	}
	printf("\n");

	printf("\t Available Resources: ");
	for (int j = 0; j < limit.columns; j++) {
		printf("%d ", stored_resources[j]);
	}
	logStart(((Thread*) t)->thread_ID);
	logFinish(((Thread*) t)->thread_ID);
	printf("\n");
	printf("\t Thread is releasing RESOURCES...\n");
	//increment the free space to stored_resources with:
	for (int j = 0; j < limit.columns; j++) {
		stored_resources[j] += allocation_matrix[i][j];
	}
	printf("\t New Available Resources: ");
	for (int j = 0; j < limit.columns; j++) {
		printf("%d ", stored_resources[j]);
	}
	printf("\n");

	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}
void resource_status() {
	isSafe();
	resources_stat();

}



//gcc -Werror -Wall -g -std=gnu99 -o Question1 Question1.c -lrt -lpthread
