/*
 * an1.interpolation.h
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */

#ifndef SRC_INTERPOLATION_AN1_INTERPOLATION_H_
#define SRC_INTERPOLATION_AN1_INTERPOLATION_H_

#include "../utils/an1.utils.h"

int interpolationMenu();

int lagrange(double (*f)(double), int npts, Vector knot, int dpts, float a, float b);

Vector buildEquidistantKnots(int npts, float a, float b);
Vector buildChebyshevKnots(int npts, float a, float b);

#endif /* SRC_INTERPOLATION_AN1_INTERPOLATION_H_ */
