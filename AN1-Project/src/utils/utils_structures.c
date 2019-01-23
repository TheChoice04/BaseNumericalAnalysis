/*
 * utils_structures.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 allocate(num, type) -> ((type*)malloc(num * sizeof(type)))
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 *	 Vector -> double*
 *	 Matrix -> double**
 */


#include "an1.utils.h"

/**
 *  Here matrix are allocated by rows so mat[i][j] is the j-th element
 *    of the i-th row.
 *
 *
 *
 */

Vector allocVector(int);
Matrix allocMatrix(int, int);
Matrix allocQMatrix(int);

Matrix parseQMatrix(int);

Vector allocRandVector(int, double, double);
Matrix allocRandMatrix(int, int, double, double);
Matrix allocRandQMatrix(int, double, double);

void multMV(Matrix A, Vector b, int m, int n, Vector* x);
void multMM(Matrix A, Matrix B, int m, int n, int l, Matrix* X);

void printVector(Vector v, int n);
void printMatrix(Matrix M, int m, int n);
void printQMatrix(Matrix M, int n);

void fprintVector(char *dest, Vector arg, int len);


//
//  Allocate Operation
//


Vector allocVector(int n){
	return allocate(n, double);
}

Matrix allocMatrix(int m, int n){
	int i;
	Matrix mat;
	mat = allocate(m, double*);
	for (i = 0; i<m; i++)
		mat[i] = allocVector(n);
	return mat;
}

Matrix allocQMatrix(int n){
	return allocMatrix(n, n);
}

Vector allocRandVector(int n, double x, double y){
	int i;
	Vector v = allocate(n, double);
	for (i=0; i<n; i++)
		v[i] = Random(x, y);
	return v;
}

Matrix allocRandMatrix(int m, int n, double x, double y){
	int i;
	Matrix mat;
	mat = allocate(m, double*);
	for (i = 0; i<m; i++)
		mat[i] = allocRandVector(n, x, y);
	return mat;
}

Matrix allocRandQMatrix(int n, double x, double y){
	return allocRandMatrix(n, n, x, y);
}

Matrix parseQMatrix(int n){
	Matrix mat;
	int i;
	double x;
	int choice;

	printf("Do you want to build a random Matrix? (1=yes/0=no)");
	scanf("%d", &choice);

	if (choice == 1){
		double x, y;
		printf("Insert minimum and maximum values for your matrix value range: ");
		scanf("%lf %lf", &x, &y);
		mat = allocRandQMatrix(n, x, y);

	} else {
		mat = allocQMatrix(n);

		for (i=0; i<n*n; i++){
			printf("Insert matrix element A[%d][%d]: ", i/n, i%n);
			scanf("%lf", &x);
			mat[i/n][i%n] = x;
		}
	}
	return mat;
}



//
//  Algebraic Operation
//


/** multMV ****************************************************************
 *
 *	This method multiplies a `m x n` Matrix `A` for a `n` Vector `b` and
 *	 stores the result in a `m` Vector `x`.
 *
 *	@param A Matrix: The matrix.
 *	@param b Vector: The vector.
 *	@param m int: The number of rows of the matrix.
 *	@param n int: The number of columns of the matrix. It must be equal
 *	               to the number of elements in the vector.
 *	@param x Vector*: The pointer to the answer vector (will be created).
 *
 *	@return NULL.
 *
 *************************************************************************/

void multMV(Matrix A, Vector b, int m, int n, Vector* x){
	int i, j;           // counters
	double sum;         // temp variable

	*x = allocVector(m);

	for (i = 0; i < m; i++){
		sum = 0.0;
		for (j = 0; j < n; j++)
			sum += (A[i][j] * b[j]);
		*x[i] = sum;
	}

	return ;
}


/** multMM ****************************************************************
 *
 *	This method multiplies a `m x n` Matrix `A` for a `n x k` Matrix `B`
 *	 and stores the result in a `m x k` Vector `x`.
 *
 *	@param A Matrix: The first matrix.
 *	@param B Matrix: The second matrix.
 *	@param m int: The number of rows of the first matrix.
 *	@param n int: The number of columns of the first matrix. It must be
 *	               equal to the number of rows of the second matrix.
 *	@param l int: The number of columns of the second matrix.
 *	@param x Matrix*: The pointer to the answer matrix (will be created).
 *
 *	@return NULL.
 *
 *************************************************************************/

void multMM(Matrix A, Matrix B, int m, int n, int l, Matrix* X){
	int i, j, k;        // counters
	double sum;         // temp variable

	*X = allocMatrix(m, l);

	for (i = 0; i < m; i++){
		for (j = 0; j < l; j++){
			sum = 0.0;
			for (k=0; k<n; k++)
				sum += (A[i][k] * B[k][j]);
			*X[i][j] = sum;
		}
	}

	return ;
}


//
//  Print Operation
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
	int i;
	for (i = 0; i < n; i++){
		printf("\t%lf", v[i]);
	}
}


/** printMatrix ***********************************************************
 *
 *	This method prints a Matrix `M`.
 *
 *	@param M Matrix: The matrix to be printed.
 *	@param m int: The number of rows.
 *	@param n int: The number of columns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printMatrix(Matrix M, int m, int n){
	int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			printf("\t%lf", M[i][j]);
		ln;
	}
}


/** printQMatrix **********************************************************
 *
 *	This method prints a square Matrix `M`.
 *
 *	@param M Matrix: The matrix to be printed.
 *	@param n int: The number of rows/columns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printQMatrix(Matrix M, int n){
	printMatrix(M, n, n);
}


//
//	File Print Operation
//


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
	int i;
	FILE *file = fopen(dest, "w");

	if (file == NULL) {
		printf("ERROR: can't open %s in writing mode.\n", dest);
		exit(1);
	}

	for (i=0; i<len; i++)
		fprintf(file, "%lf\n", arg[i]);
}
