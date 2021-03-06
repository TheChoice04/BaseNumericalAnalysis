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
#define lfpf "%+.6lf"
#define flfpf "%+.15lf"
#define DEBUG(x) printf("DEBUG %d", x);
#define max(a,b) a>=b?a:b
#define hi printf("Hello, World!\n")
#define ln printf("\n")
#define allocate(num, type) ((type*)malloc(num * sizeof(type)))
#define Random(x, y) (x + ((double) rand()/RAND_MAX)*(y-x))
#define fprintPoint(p, x, fx) fprintf(p, flfpf" "flfpf"\n", x, fx)
#define isApproxZero(x) fabs(x) < ERR
#define isApprox(x, y) fabs(x - y) < ERR
#define gnuplot(x) system("/usr/local/Cellar/gnuplot/5.2.5/bin/gnuplot "" -p 'gnuplot-scripts/"x"'")

//  Global Const Declaration
#define MAX_ATTEMPTs 1000    // 10^3,   max attempts for iterative methods
#define MAX_ERRs 5           // 5,      max number of error during choosings
#define ERR 0.0000000001     // 10^-10, default max error
#define MAX_POINTs 1000000   // 10^6,   max number of point that could be evaluated
#define CONST_DATA 1000      // 10^4,   number of data points for sample functions evaluation

//  New Type Declaration
#define Vector double*
#define Matrix double**

//
//	From utils_cloud.c
//

int parseCloud(Matrix* Pp, int *np);

//
//	From utils_function.c
//

void selectFunction(double (**f)(double), double (**df)(double));
void fprintFunction(double (*f)(double), double a, double b);

//
//  From utils_matrices.c
//

Matrix allocMatrix(int, int);
Matrix allocQMatrix(int);
Matrix allocRandMatrix(int, int, double, double);
Matrix allocRandQMatrix(int, double, double);
Matrix copyMatrix(Matrix M, int m, int n);

void multMV(Matrix A, Vector b, int m, int n, Vector x);
void multMM(Matrix A, Matrix B, int m, int n, int l, Matrix X);
void splitMatrix(Matrix A, int n, Matrix D, Matrix E, Matrix F);

int isDiagonallyDominant(Matrix M, int m, int n);
int matrixDefiniteness(Matrix M, int m, int n);

void printMatrix(Matrix M, int m, int n);
void printQMatrix(Matrix M, int n);
void fprintMatrix(char *dest, Matrix arg, int m, int n);
void fprintQMatrix(char *dest, Matrix arg, int n);

//
//	From utils_vector.c
//

Vector allocVector(int);
Vector allocRandVector(int, double, double);
Vector scanVector(int);

Vector copyVector(Vector v, int n);
void sumVV(Vector u, Vector v, int n, Vector x);

void printVector(Vector v, int n);
void fprintVector(char *dest, Vector arg, int len);

double taxicabNorm(Vector v, int n);
double euclideanNorm(Vector v, int n);
double infinityNorm(Vector v, int n);
double pNorm(Vector v, int n, int p);

//
//	From utils_systems.c
//

int parseLinearSystem(Matrix* Ap, Vector* bp, int *mp, int *np);
void updateSolution(Matrix B, Vector c, Vector x, int n);
void printSystem(Matrix, Vector, int, int);
void printSolution(Vector x, int n);
double evalSystemError(Matrix A, Vector x, Vector b, int m, int n, int p);
void printSystemError(Matrix A, Vector x, Vector b, int m, int n);

//
//	From utils_utility.c
//

int scanInt(int min, int max);
double scanDouble(double min, double max);

#endif /* SRC_UTILS_AN1_UTILS_H_ */
