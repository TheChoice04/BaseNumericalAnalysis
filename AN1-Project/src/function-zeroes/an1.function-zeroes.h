/*
 * an1.function-zeroes.h
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */

#ifndef SRC_FUNCTION_ZEROES_AN1_FUNCTION_ZEROES_H_
#define SRC_FUNCTION_ZEROES_AN1_FUNCTION_ZEROES_H_

#include "../utils/an1.utils.h"

//  Macros Declaration
#define max(a,b) a>=b?a:b
#define hi printf("Hello, World!\n")
#define ln printf("\n")
#define allocate(num, type) ((type*)malloc(num * sizeof(type)))
#define Random(x, t) (x + ((double) rand()/RAND_MAX)*(y-x))

//  Global Const Declaration
#define MAX_ATTEMPTs 10000

//
//  Execute Function
//

int functionZeroesMenu();

//
//  Execute Function
//

double exeBisection(double (*f)(double));
double exeChord(double (*f)(double));
double exeNewton(double (*f)(double), double (*f1)(double));
double exeNewtonQuotient(double (*f)(double));
double exeSecantes(double (*f)(double));
double exeSteffensen(double (*f)(double));

//
//  Direct Function
//

double bisection(double a, double b, double e, double (*f)(double));
double chord(double a, double b, double x, double e, double (*f)(double));
double newton(double x, double e, double (*f)(double), double (*f1)(double));
double newtonQuotient(double x, double h, double e, double (*f)(double));
double secantes(double xp, double x, double e, double (*f)(double));
double steffensen(double x, double e, double (*f)(double));

#endif /* SRC_FUNCTION_ZEROES_AN1_FUNCTION_ZEROES_H_ */
