//
//  mainHeader.h
//  AN410 ProjectManager
//
//  Created by Elia Onofri on 02/10/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#ifndef mainHeader_h
#define mainHeader_h

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
//     AN410 Functions
//
//  One from each .c file
//

int mainMenu();
int iterativeMenu();
int gaussianElimination();
double exeBisection(double (*f)(double));


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

//
//  From functionList.c
//

// e^x-1
double f1(double x);
double df1(double x);
// 1-sin(x)
double f2(double x);
double df2(double x);

#endif /* mainHeader_h */
