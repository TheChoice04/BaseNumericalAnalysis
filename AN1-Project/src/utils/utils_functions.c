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
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, flfpf" "flfpf"\n", x, fx)
 *	 MAX_ATTEMPTs
 *	 CONST_DATA
 */


#include "an1.utils.h"

double samplef1(double x);
double samplef2(double x);
double samplef3(double x);
double dsamplef1(double x);
double dsamplef2(double x);
double dsamplef3(double x);
void selectFunction(double (**f)(double), double (**df)(double));
void fprintFunction(double (*f)(double), double a, double b);


double samplef1(double x){
	return (exp(x) - 1);
}

double dsamplef1(double x){
	return exp(x);
}

double samplef2(double x){
	return (x/2 - sin(x));
}

double dsamplef2(double x){
	return (0.5 - cos(x));
}

double samplef3(double x){
	return (2 * x * x);
}

double dsamplef3(double x){
	return (4 * x);
}

double samplef4(double x){
	return (1. / (1. + (x * x)));
}

double dsamplef4(double x){
	return (1. / (1. + x * x));
}


/** selectFunction ********************************************************
 *
 *	Graphic menu that enumerates the available functions and makes the
 *	 user choose between them.
 *	As the derivative pointer is the first to be linked, if needed,
 *	 only function pointer could be linked via passing to copies of
 *	 the same pointer reference, like:
 *	```C
 *	double (*f)(double);
 *	selectFunction(&f, &f);
 *	```
 *
 *	@param f double **(double): pointer to the function pointer.
 *	@param df double **(double): pointer to the derivative pointer.
 *
 *	@return NULL.
 *
 *************************************************************************/

void selectFunction(double (**f)(double), double (**df)(double)){
	int c;              // choicer

	printf("Choose one of the following functions:\n");
	printf(" - type `1` to choose: (e^x)-1\n");
	printf(" - type `2` to choose: x/2-sin(x)\n");
	printf(" - type `3` to choose: 2x^2\n");
	printf(" - type `4` to choose Runge's function: 1 / (1 + x^2)\n");
	// Insert more choices here...

	c = scanInt(1, 4);
	printf("\n\n");

	switch (c){
	case 1 :
		*df = &dsamplef1;
		*f = &samplef1;
		break;

	case 2 :
		*df = &dsamplef2;
		*f = &samplef2;
		break;


	case 3 :
		*df = &dsamplef3;
		*f = &samplef3;
		break;

	case 4 :
			*df = &dsamplef4;
			*f = &samplef4;
			break;
	}


	return ;
}


/** fprintFunction ********************************************************
 *
 *	This function print on the file
 *	 `results/function-plot/functionData.txt`
 *	 the evaluation of `dpts = CONST_DATA` points of the function `f`
 *	 over the range `[a, b]`.
 *
 *	@param f duouble *(double): pointer to the function `f`.
 *	@param a double: left margin of the range.
 *	@param b double: right margin of the range.
 *
 *	@return NULL.
 *
 *************************************************************************/

void fprintFunction(double (*f)(double), double a, double b){
	int i;              // counter
	int dpts;           // number of data points
	double x = a;       // evaluation point
	double step;        // increment
	FILE *fileP;        // output file pointer

	dpts = CONST_DATA;

	fileP = fopen("results/function-plot/functionData.txt", "w");

	step = (b - a) / (dpts - 1);

	for (i = 0; i < dpts; i++){
		fprintPoint(fileP, x, f(x));
		x += step;
	}

	fclose(fileP);

	return ;
}





