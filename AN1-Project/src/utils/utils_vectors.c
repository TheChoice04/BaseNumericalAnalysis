/*
 * utils_vectors.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 allocate(num, type) -> ((type*)malloc(num * sizeof(type)))
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 *	 Vector -> double*
 */


#include "an1.utils.h"

Vector allocVector(int);
Vector allocRandVector(int, double, double);
void printVector(Vector v, int n);
void fprintVector(char *dest, Vector arg, int len);
Vector copyVector(Vector v, int n);

double taxicabNorm(Vector v, int n);
double euclideanNorm(Vector v, int n);
double infinityNorm(Vector v, int n);


//
//	allocation
//

/** allocVector ***********************************************************
 *
 *	This method simply allocate a `n` length vector.
 *
 *	@param n int: the vector length.
 *
 *	@return Vector: the vector allocated.
 *
 *************************************************************************/

Vector allocVector(int n){
	return allocate(n, double);
}


/** allocRandVector *******************************************************
 *
 *	This method allocate a `n` length vector with random values in
 *	 the range `[x, y]`.
 *
 *	@param n int: the vector length.
 *	@param x double: the minimum of the random range.
 *	@param y double: the maximum of the random range.
 *
 *	@return Vector: the vector allocated.
 *
 *************************************************************************/

Vector allocRandVector(int n, double x, double y){
	int i;              // counter
	Vector v;           // the vector

	v = allocate(n, double);
	for (i=0; i<n; i++)
		v[i] = Random(x, y);

	return v;
}


/** copyVector ************************************************************
 *
 *	This method copies the Vector `v` in a new vector.
 *
 *	@param V Matrix: the vector to be copied.
 *	@param n int: the vector length.
 *
 *	@return Vector: the copy of the input vector.
 *
 *************************************************************************/

Vector copyVector(Vector v, int n){
	int i;              // counter
	Vector c;           // the copied vector

	c = allocVector(n);

	for (i = 0; i < n; i++)
		c[i] = v[i];

	return c;
}


//
//	Print Operation
//


/** printVector ***********************************************************
 *
 *	This method prints a Vector `v`.
 *
 *	@param v Vector: The vector to be printed.
 *	@param n int: The vector length.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printVector(Vector v, int n){
	int i;              // counter

	for (i = 0; i < n; i++){
		printf("\t%lf", v[i]);
	}

	return ;
}


/** fprintVector **********************************************************
 *
 *	This method prints a Vector `arg` of length `len` over the specified
 *	 file `dest`.
 *
 *	@param dest char*: The destination file `.txt` (string path).
 *	@param arg Vector: The vector to be printed.
 *	@param len int: The vector length.
 *
 *	@return NULL.
 *
 *************************************************************************/

void fprintVector(char *dest, Vector arg, int len){
	int i;              // counter
	FILE *fileP;        // output file pointer

	fileP = fopen(dest, "w");

	if (fileP == NULL) {
		printf("ERROR: can't open %s in writing mode.\n", dest);
		exit(1);
	}

	for (i=0; i<len; i++)
		fprintf(fileP, "%lf\n", arg[i]);

	return ;
}


//
//	Normas
//


/** taxicabNorm ***********************************************************
 *
 *	This method evaluate the Taxicab norm (one norm) of the vector `v`.
 *
 *	@param `v` Vector: the vector.
 *	@param `n` int: the vector length.
 *
 *	@return double: the vector Taxicab norm.
 *
 *************************************************************************/

double taxicabNorm(Vector v, int n){
	int i;              // counter
	double norm = 0.0;  // the norm

	for (i = 0; i < n; i++)
		norm += fabs(v[i]);

	return norm;
}


/** EuclideanNorm *********************************************************
 *
 *	This method evaluate the Euclidean norm of the vector `v`.
 *
 *	@param `v` Vector: the vector.
 *	@param `n` int: the vector length.
 *
 *	@return double: the vector Taxicab norm.
 *
 *************************************************************************/

double euclideanNorm(Vector v, int n){
	int i;              // counter
	double norm = 0.0;  // the norm

	for (i = 0; i < n; i++)
		norm += (v[i] * v[i]);

	return sqrt(norm);
}


/** infinityNorm **********************************************************
 *
 *	This method evaluate the infinity norm of the vector `v`.
 *
 *	@param `v` Vector: the vector.
 *	@param `n` int: the vector length.
 *
 *	@return double: the vector Taxicab norm.
 *
 *************************************************************************/

double infinityNorm(Vector v, int n){
	int i;              // counter
	double norm = 0.0;  // the norm

	for (i = 0; i < n; i++)
		if (fabs(v[i]) > norm)
			norm = fabs(v[i]);

	return norm;
}
