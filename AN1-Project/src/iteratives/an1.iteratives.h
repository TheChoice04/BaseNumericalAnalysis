/*
 * an1.iteratives.h
 *
 *  Created on: 16 nov 2018
 *      Author: Elia
 */

#ifndef AN1_ITERATIVES_H_
#define AN1_ITERATIVES_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

int iterativeMenu();

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

//
//  From functionList.c
//

// e^x-1
double samplef1(double x);
double dsamplef1(double x);
// 1-sin(x)
double samplef2(double x);
double dsamplef2(double x);

#endif /* AN1_ITERATIVES_H_ */
