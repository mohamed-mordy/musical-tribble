/*********************************************Authorship*******************************************/
/* Author: Mohamed M. A. Mordy

   Date: August 19, 2020

   Aim: Open and read a file of integer pairs into an array that 
		is created with the first integer telling you how many to read.
	    Each pair will be a struct rational -meaning it represents a rational number.

		So a struct will have two members—the numerator and the denominator.
		So 2  9  11  4  5  would mean create an rational  array size 2 and read in the remaining 4 values into data[].
		Data[0] will be (9,11)  - the rational 9/11. Data[1] will be (4, 5)—the rational 4/5.

		Write four  routines to add rationals, multiply rationals, subtract rationals and divide rationals.
		Take the file posted with this homework and  produce the sum of all the rationals and the average
		of all the rationals in the file.

   Notes:

*/ 

/**********************************Preprocessor directives section*********************************/
#include<stdio.h>
#include<stdlib.h>

/**************************************ADT definitions section*************************************/
typedef struct
{
	int numerator;
	int denominator;
}
rational;

/********************************global variables declaration section******************************/

/*****************************functions prototypes declarations section****************************/
rational add_rational(rational a, rational b);
rational subtract_rational(rational a, rational b);
rational multiply_rational(rational a, rational b);
rational divide_rational(rational a, rational b);
double valof_rational(rational a);
rational avrof_rational(rational sum, int size);
rational reduce_rational(rational a);
unsigned int gcd(unsigned int u, unsigned int v);

/*********************************functions implementations section********************************/
// main function: Mandatory for C program to be executable
// input:  int argc, and char* argv[]
// output: int
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Need executable inputfile\n");
		exit(1);
	}
	FILE* fptr = fopen(argv[1], "r");
	int size;
	fscanf(fptr, "%d", &size);
	rational sum; sum.numerator = 0; sum.denominator = 1; // when initializing a rational to zero
	for(int i = 0; i < size; i++)                         // always make sure, the denominator is 1
	{                                                     // this is very important, and not doing
		rational a;                                       // so will lead to undefined behaviour
		fscanf(fptr, "%d", &a.numerator);
		fscanf(fptr, "%d", &a.denominator);
		printf("and the values are %d , %d", a.numerator, a.denominator);
		sum = add_rational(sum, a);
	}
	rational b = avrof_rational(sum, size);
	printf("the sum of all the rationals in the file is: (%d,%d)\n", sum.numerator, sum.denominator);
	printf("the average of all the rationals in the file is:(%d, %d)\n", b.numerator, b.denominator);
	fclose(fptr);
	return 0;
}

// add_rational function: this functions adds two rational numbers
// input: two rationals
// output: rational 
rational add_rational(rational a, rational b)
{
	rational c;
	c.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	c.denominator = a.denominator * b.denominator;
	return reduce_rational(c);
}

// subtract_rational function: subtracts two rationals
// input: two rationals
// output: rational
rational subtract_rational(rational a, rational b)
{
	b.numerator = - b.numerator;
	return reduce_rational(add_rational(a, b));
}

// multiply_rational function: multiplies two rationals
// input: two rationals
// output: rational
rational multiply_rational(rational a, rational b)
{
	rational c;
	c.numerator = a.numerator * b.numerator;
	c.denominator = a.denominator * b.denominator;
	return reduce_rational(c);
}

// divide_rational function: divides two rationals a / b
// input: two rationals
// output: rational
rational divide_rational(rational a, rational b)
{
	int c;
	c = b.numerator;
	b.numerator = b.denominator;
	b.denominator = c;
	return reduce_rational(multiply_rational(a, b));
}

// valof_rational function: returns the double value of a rational
// input: rational
// output: double
double valof_rational(rational a)
{
	return ((double) a.numerator / a.denominator);
}

// avrof_rational function: returns the average of sum of rationals as rational
// input: the sum as rational and the size
// output: rational
rational avrof_rational(rational sum, int size)
{
	rational tmp;
	tmp.numerator = size;
	tmp.denominator = 1;
	return reduce_rational(divide_rational(sum, tmp));
}

// reduce_rational function: reduces rational to its simplest form
// input: rational 
// output: rational
rational reduce_rational(rational a)
{
	// check if the numerator and the denominator is negative
	// if so, get the postive value from each of them, pass these values to gcd
	// if only the numerator or the denominator is negative, pass the positive values, and negate after
	if((a.numerator > 0 && a.denominator > 0) || (a.numerator < 0 && a.denominator < 0))
	{
		int n = gcd(abs(a.numerator), abs(a.denominator));
		a.numerator /= n;
		a.denominator /= n;
		return a;
	}
	else
	{
		int n = gcd(abs(a.numerator), abs(a.denominator));
		a.numerator /= (-n);
		a.denominator /= n;
		return a;
	}
}

// gcd function: Greatest Common Divisor, this function is copied from:
//               https://en.wikipedia.org/wiki/Binary_GCD_algorithm#Recursive_version_in_C
// input: two (unsigned int)s
// output: unsigned int
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1) // u is even
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;

    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);

    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);

    return gcd((v - u) >> 1, u);
}

/************************************testing information section***********************************/
// put the numbers which you will test against in a file and pass the file as a command line argument

/******************************************END OF THE FILE*****************************************/

