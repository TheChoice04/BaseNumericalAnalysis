/*
 * an1.interpolation.h
 *
 *  Created on: 18 dic 2018
 *      Author: Elia Onofri
 */


#ifndef SRC_INTERPOLATION_AN1_INTERPOLATION_H_
#define SRC_INTERPOLATION_AN1_INTERPOLATION_H_

#include "../utils/an1.utils.h"

//
//	interpolationMenu.c
//

int polynomialApproximationMenu();

//
//	Interpolation Functions
//

int lagrange(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b);
int newtonInterpolate(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b);

//
//	knot.c
//

Vector buildEquidistantKnots(int npts, float a, float b, int isClose);
Vector buildChebyshevKnots(int npts, float a, float b, int isClose);
Vector buildUserKnots(int npts, float a, float b, int isClose);

Vector knotFunctionValues(double (*f)(double), Vector knot, int npts);
Vector knotUserValues(Vector knot, int npts);

#endif /* SRC_INTERPOLATION_AN1_INTERPOLATION_H_ */
