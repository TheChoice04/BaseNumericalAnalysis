/*
 * an1.direct.h
 *
 *  Created on: 16 Nov 2018
 *      Author: Elia Onofri
 */

#ifndef AN1_DIRECT_H_
#define AN1_DIRECT_H_

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

//  New Type Declaration
#define Vector double*
#define Matrix double**

//
//	From gaussianElimination.c
//

int directMenu();
int gaussianElimination();

//
//  From util_Matrix.c
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

#endif /* AN1_DIRECT_H_ */
