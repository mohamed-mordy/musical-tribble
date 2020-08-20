/*********************************************Authorship*******************************************/
/* Author: Mohamed M. A. Mordy

   Date: August 21, 2020

   Aim: Open and read a file of integer into an array that 
        is created with the first integer telling you how many to read.  
        So 4 9 11 4 5 would mean create an integer array size 4 and read into data[].  
        Write a routine that places these values into a binary tree structure.
        Then walk the tree “inorder” and print these values to the screen.

   Notes: provide the input-file as a command line argument
*/ 

/**********************************Preprocessor directives section*********************************/
#include<stdio.h>
#include<stdlib.h>

/**************************************ADT definitions section*************************************/
typedef int DATA;
struct node
{
	DATA d;
	struct node* left;
	struct node* right;
};
typedef struct node NODE;
typedef NODE *BTREE;

/********************************global variables declaration section******************************/
// No global variables needed for this program

/*****************************functions prototypes declarations section****************************/
BTREE create_tree(DATA a[], int i, int size);
BTREE init_node(DATA d1, BTREE p1, BTREE p2);
BTREE new_node(void);
void in_order(BTREE root);

/*********************************functions implementations section********************************/
// main function: Mandatory for a C program to be executable
int main(int argc, char* argv[])
{
	// put stuff here
	if(argc != 2)
	{
		printf("Need executable inputfile");
		exit(1);
	}
	int size;
	FILE* fptr = fopen(argv[1], "r");
	fscanf(fptr, "%d", &size);
	DATA data[size];
	for(int i = 0; i < size; i++)
	{
		fscanf(fptr, "%d", &data[i]);
	}
	BTREE b = create_tree(data, 0, size);
	in_order(b);
	printf("\n");
	fclose(fptr);
	return 0;
}

// in_order function: traverse the binary tree
// input: BTREE
// output: void
void in_order(BTREE root)
{
	if(root != NULL)
	{
		in_order(root -> left);
		printf("%d  ", root -> d);
		in_order(root -> right);
	}
}

// new_node function: creates a new node
// input: void
// output: BTREE
BTREE new_node(void)
{
	return (malloc(sizeof(NODE)));
}

// init_node function: initializes a tree with DATA d1
// input: DATA d1, BTREE p1, BTREE p2
// output: BTREE
BTREE init_node(DATA d1, BTREE p1, BTREE p2)
{
	BTREE t = new_node();
	t -> d = d1;
	t -> left = p1;
	t -> right = p2;
	return t;
}

// create_tree function: creates from a data array
// input: DATA array, counter, size of the array
// output: BTREE
BTREE create_tree(DATA a[], int i, int size)
{
	if(i >= size)
		return NULL;
	else
		return(init_node(a[i], create_tree(a, 2 * i + 1, size), create_tree(a, 2 * i + 2, size)));
}

/**************************************************************************************************/

