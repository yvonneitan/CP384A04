/*
 -------------------------------------
 Author:  Yvonne Itangishaka
 ID:      176753040
 Email:   itan3040@mylaurier.ca
 Github Name:https://github.com/yvonneitan/CP384A04
 Version  2022-04-05
 
 -------------------------------------
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

struct Node *head;
struct Node *availble_space;
struct Node *place_holder;

char request[3], process[3], alogorithm[0];
int final_space, space_requested;

struct Node {
	int available_space;
	int start_address;
	int end_address;
	struct Node *next;
	char process_id[1000000];
};

void best_fit(char process_id[3], int space_requested) {
	//tracks the smallest space that is big enough
	int smallest_space = 999999;
	int left_space = 0;
	place_holder = head;

	//Finds the smallest possible space

	while (place_holder->next != NULL) {
		//if space is enough, track get the space
		if (strcmp(place_holder->next->process_id, "Unused") == 0
				&& place_holder->next->available_space >= space_requested) {
			//check if space is enough
			if (place_holder->next->available_space <= smallest_space)
				smallest_space = place_holder->next->available_space;
		} else
			place_holder = place_holder->next;
	}

	place_holder = head;
	//locate new process space
	while (place_holder->next != NULL) {
		//find the smallest space
		if (place_holder->next->available_space == smallest_space) {
			//calculating available space
			head->available_space = head->available_space - space_requested;

			strcpy(place_holder->next->process_id, process_id);
			place_holder->next->end_address = place_holder->next->start_address
					+ space_requested;

			left_space = place_holder->next->available_space - space_requested;
			if (left_space > 0) {
				struct Node *newNode = (struct Node*) malloc(
						sizeof(struct Node));
				strcpy(newNode->process_id, "Unused");
				newNode->available_space = left_space;
				place_holder->next->available_space = space_requested;
				newNode->start_address = place_holder->next->end_address + 1;
				newNode->end_address = newNode->start_address + left_space;
				if (newNode->end_address > final_space)
					newNode->end_address = final_space;
				newNode->next = place_holder->next->next;
				place_holder->next->next = newNode;
			}

			return; //halt the function, when space is found and inserted
		} else
			place_holder = place_holder->next;
	}

	printf("There is no space to place process %s, of %d kb\n", process_id,
			space_requested);
}

void request_memory(char process_id[3], int space_requested, char ch) {
	if (ch == 'b') {
		best_fit(process_id, space_requested);
		printf("Successfully allocated %d to process %s \n", space_requested,
				process);
	} else {
		printf("Choose B for best_fit. Try again\n");
		return;
	}
}

void releasememory(char process_id[3]) {
	printf("Releasing memory for process %s", process);

}

void memory_status() {
	place_holder = head;
	printf("Partitions [Allocated memory = %d]:", final_space);
//	printf("available space left: %d\n", head->available_space);
	while (place_holder->next != NULL) {
		printf("Address [%d : %d] Process %s\n",
				place_holder->next->start_address,
				place_holder->next->end_address,
				place_holder->next->process_id);

		printf(
				"Holes [Free memory= %d] :\n Address [0:%d] len= %s\n Address [%d:%d] len= %d\n",
				place_holder->next->start_address, final_space,
				place_holder->next->process_id,
				place_holder->next->end_address + (final_space),
				place_holder->next->end_address,
				place_holder->next->end_address - (final_space));
		place_holder = place_holder->next;
	}
}

void input_check() {
	int check = 1;
	char *input = NULL;
	ssize_t console_in = 0; //using this variable to read each line from console
	size_t input_size = 0; // stores address of the variable that holds the size of the input buffer

	while (check) {
		printf("Command>");
		console_in = getline(&input, &input_size, stdin);

		if (console_in == -1) { //error handling
			check = 0;
		}

		else {
			/* start with case handling
			 * convert input to lower case characters*/
			char *inputchar_pointer = input;
			for (; *inputchar_pointer; ++inputchar_pointer) {
				if (*inputchar_pointer == '\n') {
					*inputchar_pointer = '\0';
				} else {
					*inputchar_pointer = tolower(*inputchar_pointer);
				}
//				printf("I am in the else");
			}
			/* RQ: requesting resources*/
			/* make sure request leave system safe*/
			if (input[0] == 'R' && input[1] == 'Q' && strlen(input) >= 2) {
				request_memory(process, space_requested,
						input[strlen(input) - 1]);
			}

			/* RL: release resources and updates data structure*/
			else if (strlen(input) >= 2 && input[0] == 'R' && input[1] == 'L') {
				releasememory(process);
				printf("Successfully released memory for process %s", process);
			}

			/* if user enters Status*/
			else if (strcmp(input, "Status") == 0) {
				memory_status();
			}

			else {
				printf("Program Ended\n");
			}
		}
	}
}

int main(int argc, char *argv[]) {
	/* variable init  */
	int initial_memory = atoi(argv[1]);
	printf("Allocated %d bytes of memory \n", initial_memory);

	head = (struct Node*) malloc(sizeof(struct Node));
	availble_space = (struct Node*) malloc(sizeof(struct Node));

	/* function calls*/
	input_check();

}

//gcc Question2.c -o Question2
//./Question2 1000000
