/*
 * an1.direct.h
 *
 *  Created on: 16 Nov 2018
 *      Author: Elia Onofri
 */

#ifndef AN1_DIRECT_H_
#define AN1_DIRECT_H_

#include "../utils/an1.utils.h"

//
//	From gaussianElimination.c
//

int directMenu();
int gaussianSolution(Matrix A, Vector b, int m, int n);


#endif /* AN1_DIRECT_H_ */
