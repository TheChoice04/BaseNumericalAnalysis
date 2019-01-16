/*
 * knot.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia
 */


#include "an1.interpolation.h";


/**
 * This Method builds a `npts` Vector with equidistant Knots over `[a, b]`.
 * To do so it uses the formula:
 * ```math
 * 	x_j = a + (b - a)\frac j{npts - 1}
 * ```
 * if knots are closed or:
 * ```
 * 	x_j = a + (b - a)\frac j{npts + 1}
 * ```
 * if knots are open.
 *
 * @param npts int: number of points of the knot vector;
 * @param a double: left margin of the range;
 * @param b double: right margin of the range;
 * @param isClose int: boolean value for the closureness of the range.
 *
 * @return knot Vector: the knot vector.
 */

Vector buildEquidistantKnots(int npts, float a, float b, int isClose){
	int j;
	float step, x = a;
	Vector knot = allocVector(npts);

	if (isClose == 1)
		step = (b - a)/(npts - 1);
	else {
		step = (b - a)/(npts + 1);
		x += step;
	}
	for (j = 0; j <= npts; j++){
		knot[j] = x;
		x += step;
	}

	fprintVector("results/interpolation/knots.txt", knot, npts+1);

	return knot;
}


/**
 * This Method builds a `npts` Vector with Chebyshev Knots over `[a, b]`.
 * To do so it uses the formula:
 * ```math
 * 	x_j = a + \frac{b-a}2 (1 - \cos\frac{j\pi}n)
 * ```
 * if knots are closed or:
 * ```
 * 	x_j = a + \frac{b-a}2 (1 - \cos\frac{(2j+1)\pi}{2n+2})
 * ```
 * if knots are open.
 *
 * @param npts int: number of points of the knot vector;
 * @param a double: left margin of the range;
 * @param b double: right margin of the range;
 * @param isClose int: boolean value for the closureness of the range.
 *
 * @return knot Vector: the knot vector.
 */

Vector buildChebyshevKnots(int npts, float a, float b, int isClose){
	int j;
	float step, cosArg = 0;
	Vector knot = allocVector(npts);

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

	fprintVector("results/interpolation/knots.txt", knot, npts+1);

	return knot;

}
