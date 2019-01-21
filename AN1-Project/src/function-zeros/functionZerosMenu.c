/*
 *  functionZerosMenu.c
 *
 *  Created on: 13 nov 2018
 *      Author: Elia Onofri
 */

#include "an1.function-zeros.h"

int functionZerosMenu();

/** functionZerosMenu *****************************************************
 *
 *	This function is meant to be a menu to choose between the Iterative
 *	 algorithms for the search of a zero of a function.
 *
 *	@return int exit code:
 *	  `0` : Correct outcome
 *	  `1` : Aborted
 *	  `2` : Wrong Function Choosing
 *	  `3` : Wrong Method Choosing
 *
 *************************************************************************/

int functionZerosMenu(){
	int c;              // choicer
	int result;         // exit-code
	double a, b;		// left and right margins (Bisection, Chord)
	double e;			// error range
	double x0;          // starting point of the method (Newton, Newton Quotient, Secantes)
	double x1;          // following point of the method (Secantes)
	double h;           // fixed increment for newton quotient method (Newton Quotient)

	double (*f)(double);     // function pointer
	double (*df)(double);    // derivative pointer

	c = selectFunction();

	switch (c) {
	case 1:
		f = &samplef1;
		df = &dsamplef1;
		break;

	case 2:
		f = &samplef2;
		df = &dsamplef2;
		break;

	default:
		return 2;
	}

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Bisection;\n");
	printf(" - type `2` to Chord;\n");
	printf(" * type `3` to Muller;\n");
	printf(" - type `4` to Newton;\n");
	printf(" - type `5` to Newton Quotient;\n");
	printf(" - type `6` to Secantes;\n");
	printf(" - type `7` to Steffensen;\n");
	printf(" - type `8` to execute them all and compare the results!;\n");
	printf(" - type `0` to quit.\n");

	c = scanInt(0, 8);
	printf("\n\n");

	if (c == 1 || c == 2 || c == 8){
		printf("Type in the left and the right initialization:\n>> ");
		scanf("%lf %lf", &a, &b);
	}
	if (c == 2 || c == 4 || c == 5 || c == 8){
		printf("Type in the initial point:\n>> ");
		scanf("%lf", &x0);
	}
	if (c == 6 || c == 8){
		printf("Type in the second point:\n>> ");
		scanf("%lf", &x1);
	}
	if (c == 5 || c == 8){
		printf("Type in the fixed increment for the quotient:\n>> ");
		scanf("%lf", &h);
	}
	if (c == 0){
		printf("Correctly aborted\n");
		return 1;
	}

	printf("Type in the error range:\n>> ");
	scanf("%lf", &e);

	switch (c) {
	case 1:
		result = bisection(a, b, e, f);
		break;

	case 2:
		result = chord(a, b, x0, e, f);
		break;

	case 3:
		//result = exeMuller(f);
		break;

	case 4:
		result = newton(x0, e, f, df);
		break;

	case 5:
		result = newtonQuotient(x0, h, e, f);
		break;

	case 6:
		result = secantes(x0, x1, e, f);
		break;

	case 7:
		result = steffensen(x0, e, f);
		break;

	case 8:
		printf("\n\n\nExecuting Bisection method...\n\n");
		bisection(a, b, e, f);

		printf("\n\n\nExecuting Chord method...\n\n");
		chord(a, b, x0, e, f);

		//printf("\nExecuting  method...\n\n");
		//result = exeMuller(f);

		printf("\n\n\nExecuting Newton method...\n\n");
		newton(x0, e, f, df);

		printf("\n\n\nExecuting Newton Quotient method...\n\n");
		newtonQuotient(x0, h, e, f);

		printf("\n\n\nExecuting Secantes method...\n\n");
		secantes(x0, x1, e, f);

		printf("\n\n\nExecuting Steffensen method...\n\n");
		steffensen(x0, e, f);
		break;

	case 0:
		printf("Aborted\n");
		return 1;

	default:
		printf("ERROR: no function for the choice made.");
		return 3;
	}

	return 0;
}

