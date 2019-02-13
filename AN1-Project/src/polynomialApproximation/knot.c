/*
 * knot.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
 *	 MAX_POINTs
 *	 MAX_ERRs
 */


#include "an1.polynomialApproximation.h"

Vector buildEquidistantKnots(int npts, float a, float b, int isClose);
Vector buildChebyshevKnots(int npts, float a, float b, int isClose);
Vector buildUserKnots(int npts, float a, float b, int isClose);

Vector knotFunctionValues(double (*f)(double), Vector knot, int npts);
Vector knotUserValues(Vector knot, int npts);


/** buildEquidistantKnots *************************************************
 *
 *	This Method builds a `npts` Vector with equidistant Knots over `[a, b]`.
 *	To do so it uses the formula:
 *	```math
 *	x_j = a + (b - a)\frac j{npts - 1}
 *	```
 *	 if knots are closed or:
 *	```
 *	x_j = a + (b - a)\frac j{npts + 1}
 *	```
 *	 if knots are open.
 *
 *	The knot are printed on the file:
 *	`results/polynomialApproximation/knots.txt`
 *
 *	@param npts int: number of points of the knot vector.
 *	@param a double: left margin of the range.
 *	@param b double: right margin of the range.
 *	@param isClose int: boolean value for the closureness of the range.
 *
 *	@return Vector: the knot vector.
 *
 *************************************************************************/

Vector buildEquidistantKnots(int npts, float a, float b, int isClose){
	int j;              // counter
	float step;         // step between knots
	Vector knot;        // the knot vector

	knot = allocVector(npts);

	if (isClose == 1){
		step = (b - a)/(npts - 1);
		knot[0] = a;
	}
	else {
		step = (b - a)/(npts + 1);
		knot[0] = a + step;
	}
	for (j = 1; j < npts; j++){
		knot[j] = knot[j - 1] + step;
	}

	fprintVector("results/polynomialApproximation/knots.txt", knot, npts);

	return knot;
}


/** buildChebyshevKnots ***************************************************
 *
 *	This Method builds a `npts` Vector with Chebyshev Knots over `[a, b]`.
 *	To do so it uses the formula:
 *	```math
 *	x_j = a + \frac{b-a}2 (1 - \cos\frac{j\pi}n)
 *	```
 *	 if knots are closed or:
 *	```
 *	x_j = a + \frac{b-a}2 (1 - \cos\frac{(2j+1)\pi}{2n+2})
 *	```
 *	 if knots are open.
 *
 *	The knot are printed on the file:
 *	 `results/polynomialApproximation/knots.txt`
 *
 *	@param npts int: number of points of the knot vector.
 *	@param a double: left margin of the range.
 *	@param b double: right margin of the range.
 *	@param isClose int: boolean value for the closureness of the range.
 *
 *	@return Vector: the knot vector.
 *
 *************************************************************************/

Vector buildChebyshevKnots(int npts, float a, float b, int isClose){
	int j;              // counter
	float step;         // step between cos arguments
	float cosArg = 0;   // cos argument
	Vector knot;        // knot vector

	knot = allocVector(npts);

	if (isClose == 1)
		step = M_PI/(npts - 1);
	else {
		step = M_PI/npts;
		cosArg = step/2;
	}
	for (j = 0; j <= npts; j++){
		knot[j] = a + (b - a)/2 * (1 - cos(cosArg));
		cosArg += step;
	}

	fprintVector("results/polynomialApproximation/knots.txt", knot, npts);

	return knot;

}


/** buildUserKnots ********************************************************
 *
 *	This Method reads a `npts` Vector from keyboard over `[a, b]`.
 *
 *	The knot are printed on the file:
 *	`results/polynomialApproximation/knots.txt`
 *
 *	@param npts int: number of points of the knot vector.
 *	@param a double: left margin of the range.
 *	@param b double: right margin of the range.
 *	@param isClose int: boolean value for the closureness of the range.
 *
 *	@return Vector: the knot vector.
 *
 *************************************************************************/

Vector buildUserKnots(int npts, float a, float b, int isClose){
	int i = 0;          // counter
	int err = 0;        // errors counter
	double x;           // reader;
	Vector knot;        // knot vector

	knot = allocVector(npts);

	if (isClose == 1){
		printf("Type in %d points in the range `[%lf, %lf]`.\n", npts, a, b);
		printf("TIP: Typing in one at time could be safer!.\n");
		while (i < npts){
			printf(">> ");
			scanf("%lf", &x);
			if (x >= a && x <= b){
				knot[i] = x;
				i++;
			} else if (err < MAX_ERRs){
				printf("WARNING: The value is not within the range `[%lf, %lf]`.\n", a, b);
				printf("         Please choose another value.               (%d)\n", MAX_ERRs-err);
				err++;
			} else {
				exit(8);
			}
		}
	} else {
		printf("Type in %d points in the range `(%lf, %lf)`.\n", npts, a, b);
		printf("TIP: Typing in one at time could be safer!.\n");
		while (i < npts){
			printf(">> ");
			scanf("%lf", &x);
			if (x > a && x < b){
				knot[i] = x;
				i++;
			} else if (err < MAX_ERRs){
				printf("WARNING: The value is not within the range `(%lf, %lf)`.\n", a, b);
				printf("         Please choose another value.               (%d)\n", MAX_ERRs-err);
				err++;
			} else {
				exit(8);
			}
		}
	}

	fprintVector("results/polynomialApproximation/knots.txt", knot, npts);

	return knot;
}


/** knotFunctionValues ****************************************************
 *
 *	This Method evaluates a `knot` Vector with a function `f`.
 *
 *	The tuples `knot - knot value` are printed on the file:
 *	`results/polynomialApproximation/knot_values.txt`
 *
 *	@param f double *(double): the function.
 *	@param knot Vector: the knot vector.
 *	@param npts int: number of points of the knot vector.
 *
 *	@return Vector: the knot values vector.
 *
 *************************************************************************/

Vector knotFunctionValues(double (*f)(double), Vector knot, int npts){
	int i;              // counter
	Vector knotVal;     // knot vector
	FILE *fileP;        // output file pointer

	fileP = fopen("results/polynomialApproximation/knot_values.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/polynomialApproximation/knot_values.txt` in writing mode.\n");
		exit(1);
	}

	knotVal = allocVector(npts);

	for (i = 0; i < npts; i++){
		knotVal[i] = f(knot[i]);
		fprintPoint(fileP, knot[i], knotVal[i]);
	}

	fclose(fileP);

	return knotVal;
}


/** knotUserValues ********************************************************
 *
 *	This Method reads the value of a `knot` Vector from the keyboard.
 *
 *	The tuples `knot - knot value` are printed on the file:
 *	`results/polynomialApproximation/knot_values.txt`
 *
 *	@param knot Vector: the knot vector.
 *	@param npts int: number of points of the knot vector.
 *
 *	@return Vector: the knot values vector.
 *
 *************************************************************************/

Vector knotUserValues(Vector knot, int npts){
	int i;              // counter
	double x;           // reader
	Vector knotVal;     // knot vector
	FILE *fileP;        // output file pointer

	fileP = fopen("results/polynomialApproximation/knot_values.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/polynomialApproximation/knot_values.txt` in writing mode.\n");
		exit(1);
	}


	knotVal = allocVector(npts);

	for (i = 0; i < npts; i++){
		printf("Type in the value from the %d-th knot "lfpf".\n>> ", i, knot[i]);
		scanf("%lf", &x);
		knotVal[i] = x;
		fprintPoint(fileP, knot[i], knotVal[i]);
	}

	fclose(fileP);

	return knotVal;
}
