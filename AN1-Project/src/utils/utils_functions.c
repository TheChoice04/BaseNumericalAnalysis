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
 *	 fprintPoint(p, x, fx) -> fprintf(p, "%lf %lf\n", x, fx)
 *	 MAX_ATTEMPTs
 *	 CONST_DATA
 */


#include "an1.utils.h"

double samplef1(double x);
double samplef2(double x);
double dsamplef1(double x);
double dsamplef2(double x);
void selectFunction(double (**f)(double), double (**df)(double));
void fprintFunction(double (*f)(double), double a, double b);


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
	printf(" - type '1' to choose: (e^x)-1\n");
	printf(" - type '2' to choose: x/2-sin(x)\n");
	// Insert more choices here...

	c = scanInt(1, 2);
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
	}

	return ;
}


/** fprintFunction ********************************************************
 *
 *	This function print on the file
 *	 `results/function-plot/functionData.txt`
 *	 the evaluation of `dpts = 1000` points of the function `f` over
 *	 the range `[a, b]`.
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
	double x = 0;       // evaluation point
	double step;        // increment
	FILE *fileP;        // output file pointer

	printf("Evaluating reference function...");
	dpts = CONST_DATA;

	fileP = fopen("results/function-plot/functionData.txt", "w");

	step = (b - a) / (dpts - 1);

	for (i = 0; i < dpts; i++){
		fprintPoint(fileP, x, f(x));
	}

	fclose(fileP);

	printf("...reference function evaluated.");
	return ;
}





