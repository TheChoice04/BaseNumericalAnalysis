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

#define max(a,b) a>=b?a:b
#define hi printf("Hello, World!\n")
#define ln printf("\n")
#define allocate(num, type) ((type*)malloc(num * sizeof(type)))

#define Vector double*
#define Matrix double**


//
//     AN410 Functions
//
//  One from each .c file
//

int mainMenu();
int gaussianElimination();

//
//  From util_Matrix.c
//


Vector allocVector(int);
Matrix allocMatrix(int, int);
Matrix allocQMatrix(int);

Vector multMV(int, int, Matrix, int, Vector);
Matrix multMM(int, int, Matrix, int, int, Matrix);

void printVector(int, Vector);
void printMatrix(int, int, Matrix);
void printQMatrix(int, Matrix);


#endif /* mainHeader_h */
