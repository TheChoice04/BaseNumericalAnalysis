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
 *	 Matrix -> double**
 */


#include "an1.utils.h"

Vector allocVector(int);
Vector allocRandVector(int, double, double);
void printVector(Vector v, int n);
void fprintVector(char *dest, Vector arg, int len);

double taxicabanNorm();
double euclideanNorm();
double infinityNorm();


//
//	allocation
//

/** allocVector ***********************************************************
 *
 *	This method simply allocate a `n` length vector.
 *
 *	@param n int: vector length.
 *
 *	@return Vector allocated
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
 *	@param n int: vector length.
 *	@param x double: min of the random range.
 *	@param y double: max of the random range.
 *
 *	@return Vector allocated
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

	*fileP = fopen(dest, "w");

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
