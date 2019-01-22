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

int interpolationMenu();

//
//	lagrange.c
//

void lagrange(double (*f)(double), int npts, Vector knot, int dpts, float a, float b);
void diplayLagrange(int dpts);

//
//	knot.c
//

Vector buildEquidistantKnots(int npts, float a, float b, int isClose);
Vector buildChebyshevKnots(int npts, float a, float b, int isClose);

#endif /* SRC_INTERPOLATION_AN1_INTERPOLATION_H_ */
