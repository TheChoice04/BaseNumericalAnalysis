/*
 * knot.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
 *	 MAX_POINTs
 */


#include "an1.interpolation.h"

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
 *	@param npts int: number of points of the knot vector;
 *	@param a double: left margin of the range;
 *	@param b double: right margin of the range;
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

	fprintVector("results/interpolation/knots.txt", knot, npts);

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
 *	@param npts int: number of points of the knot vector;
 *	@param a double: left margin of the range;
 *	@param b double: right margin of the range;
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

	fprintVector("results/interpolation/knots.txt", knot, npts);

	return knot;

}
