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

int iterativeMenu();
double exeBisection(double (*f)(double));

//
//  From functionList.c
//

// e^x-1
double f1(double x);
double df1(double x);
// 1-sin(x)
double f2(double x);
double df2(double x);

#endif /* AN1_ITERATIVES_H_ */
