/*********************************************Authorship*********************************************/
/* Author: Mohamed M. A. Mordy
// DAte: August 19, 2020
// Aim: Implementation of a program that takes the data of the first 10 elements of the periodic table
//      from the user, stores the data in a linked list, and prints the data in a tabular form.
// Notes: Look at the end of this file for a very important information of how to simplify testing
//        process of this code.
//
//
*/
/**********************************preprocessor directives section**********************************/
#include<stdio.h>
#include<stdlib.h>
#define MAX 10 // The length of the longest name of the elements in the periodic table
               // it may be changed as needed.
			   // this is used to control the length of the string, look at struct atom!

/***************************************ADT definitions sections*************************************/
typedef struct            // This struct represents the information of the atom of an element
{
	char name[MAX];
	char symbol[MAX];
	double weight;
} atom;

struct list               // This struct is used in the implementation of the linked list
{
	atom element;        // It carries an atom and a pointer to the next element
	struct list* next;
};
typedef struct list list; // simplifying things

/********************************global variables declarations section*******************************/
// No global variables are needed in this program

/******************************functions prototype declarations section******************************/
list* create_list(atom a);
list* add_to(atom a, list* l);
void print_list(list* head);
list* get_input(void);

/**********************************functions implementations section********************************/
// main function: Mandatory for a C program to be executable
// input: void i.e. no input
// output: int, typically 0 which is a message to the system that every thing is ok
int main(void)
{
	list* ptr = get_input();
	print_list(ptr);
	return 0;
}

// create_list function: this function is to create a linked list 
// input: atom
// output: pointer to the head of the list
list* create_list(atom a)
{
	list* head = malloc(sizeof(list));
	head -> element = a;
	head -> next = NULL;
	return head;
}

// add_to function: this function adds an element to an existing list
// input: atom and pointer to the linked list
// output: pointer to the head of the linked list
list* add_to(atom a, list* l)
{
	list* head = malloc(sizeof(list));
	head -> element = a;
	head -> next = l;
	return head;
}
	
// print_list function: prints out the data from the linked list in a tabular form
// input: pointer to the head of the list
// output: void i.e. no output, only side-effects
void print_list(list* head)
{
	// This function may look little confusing, but it works fine.
	for(int i = 0; i < 16*3; i++){printf("_");}printf("\n");
	printf("|%-10s\t|%-10s\t|%-10s\t|\n", "Name", "symbol", "Weight");
	for(int i = 0; i < 3; i++)
	{
		printf("|");
		for(int j = 0; j < 15; j++)
		{
			printf("_");
		}
	}
	printf("|");
	printf("\n");
	while(head != NULL)
	{
		printf("|%-10s\t|%-10s\t|%-10f\t|\n", head -> element.name, head -> element.symbol, head -> element.weight);
		for(int i = 0; i < 3; i++)
		{
			printf("|");
			for(int j = 0; j < 15; j++)
			{
				printf("_");
			}
		}
		printf("|");
		printf("\n");
		head = head -> next;
	}
}

// get_input function: get the input from the user using scanf.
// input: void.
// output: pointer to the linked list that carries the data.
list* get_input(void)
{
	atom temp;
	scanf("%s", &(temp.name));
	scanf("%s", &(temp.symbol));
	scanf("%lf", &(temp.weight));
	list* head = create_list(temp);
	for(int i = 0; i < 9; i++)
	{
	 	scanf("%s", &(temp.name));
		scanf("%s", &(temp.symbol));
		scanf("%lf", &(temp.weight));
		head = add_to(temp, head);
	}
	return head;
}

/*******************************Important information for code testers*******************************/
/* copy the following 30 line, put them in file input.txt, compile as gcc atom.c -o atom, execute as atom < input.txt
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
foo
bar
1.333
*/

