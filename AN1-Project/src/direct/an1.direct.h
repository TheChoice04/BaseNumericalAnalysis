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
//	From directMenu.c
//

int directMenu();

//
//	From gaussianElimination.c
//

int gaussianSolution(Matrix A, Vector b, int m, int n, Vector x);


//
//	From triangularSolver.c
//

int triSupSolver(Matrix A, Vector b, int m, int n, Vector x);
int triInfSolver(Matrix A, Vector b, int m, int n, Vector x);


#endif /* AN1_DIRECT_H_ */
