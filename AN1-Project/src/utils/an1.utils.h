/*
 * an1.utils.h
 *
 *  Created on: 16 gen 2019
 *      Author: Elia
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
#define Random(x, t) (x + ((double) rand()/RAND_MAX)*(y-x))

//  Global Const Declaration
#define MAX_ATTEMPTs 10000
#define MAX_ERRs 5

//  New Type Declaration
#define Vector double*
#define Matrix double**

//
//	From utils_function.c
//

double samplef1(double x);
double samplef2(double x);
double dsamplef1(double x);
double dsamplef2(double x);

int selectFunction();

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
