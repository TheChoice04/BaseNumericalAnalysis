/*
 * interpolationMenu.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia
 */


#include "an1.interpolation.h"

/**
 * This function is meant to be a menu to choose between the Iterative
 *  algorithms for the search of a zero of a function.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 *      `4` : Aborted
 */

int interpolationMenu(){
	int c, npts;
	double result;
	double (*f)(double);

	//==========FUNCTION CHOOSING
	c = selectFunction();
	switch (c) {
	case 1:
		f = &samplef1;
		break;

	case 2:
		f = &samplef2;
		break;

	default:
		printf("ERROR: no function for the choice made.");
		return 2;
	}

	//==========KNOT CHOOSING

	printf("How many knots do you want to build? ");
	scanf("%d", &npts);

	printf("You can choose one of the Knot Construction:\n");
	printf(" - type `1` to build %d equidistant knots (ToDo);\n", npts);
	printf(" - type `2` to build %d Chebyshev knots (ToDo);\n", npts);
	// Insert more choices here...
	printf(" - type `0` to abort.\n\n");
	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	switch (c) {
	case 1:
		//k = buildEquidistantKnots(n+1);
		break;

	case 2:
		//k = buildChebyshevKnots(n+1);
		break;
	case 0:
		printf("Aborted\n");
		return 4;

	default:
		printf("ERROR: no function for the choice made.");
		return 3;
	}

	//==========INTERPOLATION CHOOSING

	printf("You can choose one of the following Interpolation Methods:\n");
	printf(" - type `1` to Lagrange Interpolation;\n");
	printf(" - type `2` to Newton Interpolation (NY);\n");
	printf(" - type `3` to Hermite Interpolation (NY);\n");
	// Insert more choices here...
	printf(" - type `0` to abort.\n\n");
	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	switch (c) {
	case 1:
		//result = exeLagrange(f);
		break;

	case 2:
		//result = exeNewton(f);
		break;

	case 3:
		//result = exeHermite(f);
		break;

	case 0:
		printf("Aborted\n");
		return 4;

	default:
		printf("ERROR: no function for the choice made.");
		return 3;
	}

	return 0;
}
