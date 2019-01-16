/*
 * utils_function.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 */


#include "an1.utils.h"

/**
 * Everywhere in the code you can say
 *  double *f(double);
 *  f = &samplef1;
 * to set a fix value for f.
 */

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


int selectFunction(){
	int c;

	printf("Choose one of the following functions:\n");
	printf(" - type '1' to choose: (e^x)-1\n");
	printf(" - type '2' to choose: x/2-sin(x)\n");
	// Insert more choices here...

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	return c;
}
