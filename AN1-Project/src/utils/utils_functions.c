/*
 * utils_function.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	This file is a library of sample functions used to test the codes.
 *	Reachable everywhere from the code with the following syntax:
 *	```C
 *	double *f(double);
 *  f = &samplef1;
 *	```
 */


#include "an1.utils.h"

double samplef1(double x);
double samplef2(double x);
double dsamplef1(double x);
double dsamplef2(double x);
int selectFunction();


double samplef1(double x){
	return exp(x)-1;
}

double dsamplef1(double x){
	return exp(x);
}

double samplef2(double x){
	return x/2-sin(x);
}

double dsamplef2(double x){
	return 1/2-cos(x);
}


/** selectFunction ********************************************************
 *
 * Graphic menu that enumerates the available functions.
 *
 *	@return int the choice `c` made.
 *
 *************************************************************************/

int selectFunction(){
	int c;              // choicer

	printf("Choose one of the following functions:\n");
	printf(" - type '1' to choose: (e^x)-1\n");
	printf(" - type '2' to choose: x/2-sin(x)\n");
	// Insert more choices here...

	c = scanInt(1, 2);
	printf("\n\n");

	return c;
}
