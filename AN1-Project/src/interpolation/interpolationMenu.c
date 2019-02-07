/*
 * interpolationMenu.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
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
 *      `0` : Correct outcome.
 *      `3` : Method not encoded yet.
 *
 *************************************************************************/

int interpolationMenu(){
	int c;              // choicer
	int i;              // counter
	int p;              // norm value
	int ans;            // interpolation exit-code
	int npts;           // number of knot points
	int dpts;           // number of data points
	int isClose;        // boolean value fir closure
	double a, b;        // left and right margin of the range
	double norm;        // norm value
	double delta;       // delta for each data point
	Vector err;         // error vector
	Vector knot;        // knot vector
	Vector knotVal;     // knot values
	FILE *fileP;        // file pointer to method response
	double (*f)(double);     // function pointer

	selectFunction(&f, &f);

	//==========KNOT CHOOSING

	printf("Type in left and right edge of the range:\n>> ");
	scanf("%lf %lf", &a, &b);

	printf("Type in the number of data points you want to evaluate.\n");
	dpts = scanInt(1, MAX_POINTs);

	printf("How many knots do you want to build?\n");
	npts = scanInt(1, MAX_POINTs);

	printf("What kind of knot do you want to build?\n");
	printf(" - type `0` for open knots;\n");
	printf(" - type `1` for close knots;\n");
	isClose = scanInt(0, 1);

	printf("What kind of Knot Construction do you want?\n");
	printf(" - type `1` to build %d equidistant knots;\n", npts);
	printf(" - type `2` to build %d Chebyshev knots;\n", npts);
	printf(" - type `3` to manually insert the %d knots.\n", npts);
	c = scanInt(1, 3);

	switch (c) {
	case 1:
		knot = buildEquidistantKnots(npts, a, b, isClose);
		break;

	case 2:
		knot = buildChebyshevKnots(npts, a, b, isClose);
		break;

	case 3:
		knot = buildUserKnots(npts, a, b, isClose);
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;
	}

	printf("Where do you want to take the knot value from?\n");
	printf(" - type `1` to get the values from the function;\n");
	printf(" - type `2` to get the values from the keyboard;\n");
	c = scanInt(1, 2);

	switch (c) {
	case 1:
		knotVal = knotFunctionValues(f, knot, npts);
		break;

	case 2:
		knotVal = knotUserValues(knot, npts);
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		free(knot);
		return 3;
	}


	//==========INTERPOLATION CHOOSING

	printf("Choose a norm for the evaluation:\n");
	printf(" - type `1` for taxicab norm.\n");
	printf(" - type `2` for euclidean norm.\n");
	printf(" - type `0` for infinite norm.\n");
	p = scanInt(0, 2);

	//==========INTERPOLATION CHOOSING

	printf("You can choose one of the following Interpolation Methods:\n");
	printf(" - type `1` to Lagrange Interpolation;\n");
	printf(" * type `2` to Newton Interpolation;\n");
	printf(" * type `3` to Hermite Interpolation.\n");
	c = scanInt(1, 3);

	err = allocVector(dpts);

	switch (c) {
	case 1:
		ans = lagrange(f, npts, knot, knotVal, dpts, a, b);
		if (ans == 0)
			gnuplot("interpolation/lagrange.gp");

		fileP = fopen("results/interpolation/lagrange_interpolate.txt", "r");

		if (fileP == NULL) {
			printf("ERROR: can't open `results/interpolation/lagrange_interpolate.txt` in reading mode.\n");
			exit(1);
		}

		for (i = 0; i < dpts; i++){
			fscanf(fileP, "%lf %lf %lf %lf", &delta, &delta, &delta, &delta);
			err[i] = delta;
		}

		fclose(fileP);
		break;

		/*	case 2:
		ans = exeNewton(f);
		break;

	case 3:
		ans = exeHermite(f);
		break;
		 */

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		free(knot);
		free(knotVal);
		free(err);
		return 3;
	}

	if (ans == 0){
		norm = pNorm(err, dpts, p);
		printf("The Norm error over the %d data points is %lf.\n", dpts, norm);
	}


	free(knot);
	free(knotVal);
	free(err);

	return 0;
}
