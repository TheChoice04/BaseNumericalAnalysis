/*
 * interpolationMenu.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector double*
 *	 MAX_POINTs
 */


#include "an1.interpolation.h"

int interpolationMenu();


/** interpolationMenu *****************************************************
 *
 * This function is meant to be a menu to choose between the interpolation
 *  algorithms to approximate a given function.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `1` : Aborted
 *      `3` : Wrong Method Choosing
 *      `4` : Wrong
 *
 *************************************************************************/

int interpolationMenu(){
	int c;              // choicer
	int npts;           // number of knot points
	int dpts;           // number of data points
	int isClose;        // boolean value fir closure
	double a, b;        // left and right margin of the
	Vector knot;        // Knot vector
	double (*f)(double);     // function pointer

	selectFunction(&f, &f);

	//==========KNOT CHOOSING

	printf("Type in left and right edge of the range:\n>> ");
	scanf("%lf %lf", &a, &b);

	printf("Type in the number of data points you want to evaluate.\n");
	dpts = scanInt(1, MAX_POINTs);

	printf("How many knots do you want to build?\n");
	npts = scanInt(1, MAX_POINTs);

	printf(" - type `0` for open knots\n");
	printf(" - type `1` for close knots\n");
	isClose = scanInt(0, 1);

	printf("What kind of Knot Construction do you want?\n");
	printf(" - type `1` to build %d equidistant knots;\n", npts);
	printf(" - type `2` to build %d Chebyshev knots;\n", npts);
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 2);

	switch (c) {
	case 1:
		knot = buildEquidistantKnots(npts, a, b, isClose);
		break;

	case 2:
		knot = buildChebyshevKnots(npts, a, b, isClose);
		break;
	case 0:
		printf("Aborted\n");
		return 1;

	default:
		printf("ERROR: no methods for the choice made.");
		return 5;
	}

	//==========INTERPOLATION CHOOSING

	printf("You can choose one of the following Interpolation Methods:\n");
	printf(" - type `1` to Lagrange Interpolation;\n");
	printf(" * type `2` to Newton Interpolation;\n");
	printf(" * type `3` to Hermite Interpolation;\n");
	// Insert more choices here...
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 3);

	switch (c) {
	case 1:
		lagrange(f, npts, knot, dpts, a, b);
		break;

/*	case 2:
		ans = exeNewton(f);
		break;

	case 3:
		ans = exeHermite(f);
		break;
*/
	case 0:
		printf("Aborted\n");
		return 1;

	default:
		printf("ERROR: no method for the choice made.");
		return 3;
	}

	return 0;
}
