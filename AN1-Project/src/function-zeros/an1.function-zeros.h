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
//  Execute Function
//


double exeNewton(double (*f)(double), double (*f1)(double));
double exeNewtonQuotient(double (*f)(double));
double exeSecantes(double (*f)(double));
double exeSteffensen(double (*f)(double));

//
//  Direct Function
//

int bisection(double a, double b, double e, double (*f)(double));
int chord(double a, double b, double x, double e, double (*f)(double));
double newton(double x, double e, double (*f)(double), double (*f1)(double));
double newtonQuotient(double x, double h, double e, double (*f)(double));
double secantes(double xp, double x, double e, double (*f)(double));
double steffensen(double x, double e, double (*f)(double));

#endif /* SRC_FUNCTION_ZEROS_AN1_FUNCTION_ZEROS_H_ */
