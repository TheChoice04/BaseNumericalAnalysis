/*
 * an1.iteratives.h
 *
 *  Created on: 23 gen 2019
 *      Author: Elia
 */

#ifndef SRC_ITERATIVES_AN1_ITERATIVES_H_
#define SRC_ITERATIVES_AN1_ITERATIVES_H_

#include "../utils/an1.utils.h"


int iterativeMenu();

// functions
int jacobi(Matrix A, Vector b, int n, Vector x, double err, int p);

#endif /* SRC_ITERATIVES_AN1_ITERATIVES_H_ */
