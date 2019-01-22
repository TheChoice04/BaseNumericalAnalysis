/*
 * an1.utils.h
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 */

#ifndef SRC_UTILS_AN1_UTILS_H_
#define SRC_UTILS_AN1_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//  Macros Declaration
#define max(a,b) a>=b?a:b
#define hi printf("Hello, World!\n")
#define ln printf("\n")
#define allocate(num, type) ((type*)malloc(num * sizeof(type)))
#define Random(x, y) (x + ((double) rand()/RAND_MAX)*(y-x))
#define fprintPoint(p, x, fx) fprintf(p, "%lf %lf\n", x, fx);

//  Global Const Declaration
#define MAX_ATTEMPTs 1000    // 10^3 max attempts for iterative methods
#define MAX_ERRs 5           // max number of error during choosings
#define ERR 0.0000000001     // 10^-10, default max error
#define MAX_POINTs 1000000   // 10^6, max number of point that could be evaluated
#define CONST_DATA 1000      // 10^4, number of data points for sample functions evaluation

//  New Type Declaration
#define Vector double*
#define Matrix double**

//
//	From utils_function.c
//

void selectFunction(double (**f)(double), double (**df)(double));

//
//  From utils_structures.c
//

Vector allocVector(int);
Matrix allocMatrix(int, int);
Matrix allocQMatrix(int);

Matrix parseQMatrix(int);

Vector allocRandVector(int, double, double);
Matrix allocRandMatrix(int, int, double, double);
Matrix allocRandQMatrix(int, double, double);

Vector multMV(int, int, Matrix, int, Vector);
Matrix multMM(int, int, Matrix, int, int, Matrix);

void printVector(int, Vector);
void printMatrix(int, int, Matrix);
void printQMatrix(int, Matrix);
void printSystem(Matrix, Vector, int, int);

void fprintVector(char *dest, Vector arg, int len);

//
//	From utils_utility.c
//

int scanInt(int min, int max);

#endif /* SRC_UTILS_AN1_UTILS_H_ */
