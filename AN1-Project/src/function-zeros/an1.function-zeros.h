/*
 * an1.function-zeros.h
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */

#ifndef SRC_FUNCTION_ZEROS_AN1_FUNCTION_ZEROS_H_
#define SRC_FUNCTION_ZEROS_AN1_FUNCTION_ZEROS_H_

#include "../utils/an1.utils.h"

//
//  fromfunctionZerosMenu.c
//

int functionZerosMenu();

//
//  Direct Function
//

int bisection(double a, double b, double e, double (*f)(double));
int chord(double a, double b, double x, double e, double (*f)(double));
int newton(double x, double e, double (*f)(double), double (*f1)(double));
int newtonQuotient(double x, double h, double e, double (*f)(double));
int secantes(double xp, double x, double e, double (*f)(double));
int steffensen(double x, double e, double (*f)(double));

#endif /* SRC_FUNCTION_ZEROS_AN1_FUNCTION_ZEROS_H_ */
