/*
 * utils_matrices.c
 *
 *  Created on: 16 gen 2019
 *      Author: Elia Onofri
 **
 *	Here matrix are allocated by rows so mat[i][j] is the j-th element
 *	 of the i-th row.
 **
 *	Macros used:
 *	 allocate(num, type) -> ((type*)malloc(num * sizeof(type)))
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 *	 Vector -> double*
 *	 Matrix -> double**
 */


#include "an1.utils.h"

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
//  Allocate Operation
//


/** allocMatrix ***********************************************************
 *
 *	This method simply allocate a `m x n` matrix.
 *
 *	@param m int: the number of rows.
 *	@param n int: the number of columns.
 *
 *	@return Matrix: the matrix allocated.
 *
 *************************************************************************/

Matrix allocMatrix(int m, int n){
	int i;              // counter
	Matrix mat;         // new matrix

	mat = allocate(m, double*);
	for (i = 0; i<m; i++)
		mat[i] = allocVector(n);

	return mat;
}


/** allocQMatrix **********************************************************
 *
 *	This method allocate a square `n x n` matrix.
 *
 *	@param n int: the number of rows/columns.
 *
 *	@return Matrix: the matrix allocated.
 *
 *************************************************************************/

Matrix allocQMatrix(int n){
	return allocMatrix(n, n);
}


/** allocRandMatrix *******************************************************
 *
 *	This method allocate a `m x n` matrix with random values in
 *	 the range `[x, y]`.
 *
 *	@param m int: the number of rows.
 *	@param n int: the number of columns.
 *	@param x double: the minimum of the random range.
 *	@param y double: the maximum of the random range.
 *
 *	@return Matrix: the matrix allocated.
 *
 *************************************************************************/

Matrix allocRandMatrix(int m, int n, double x, double y){
	int i;              // counter
	Matrix mat;         // new matrix

	mat = allocate(m, double*);
	for (i = 0; i<m; i++)
		mat[i] = allocRandVector(n, x, y);

	return mat;
}


/** allocRandQMatrix ******************************************************
 *
 *	This method allocate a square `n x n` matrix with random values in
 *	 the range `[x, y]`.
 *
 *	@param n int: the number of rows/columns.
 *	@param x double: the minimum of the random range.
 *	@param y double: the maximum of the random range.
 *
 *	@return Matrix: the matrix allocated.
 *
 *************************************************************************/

Matrix allocRandQMatrix(int n, double x, double y){
	return allocRandMatrix(n, n, x, y);
}


/** copyMatrix ************************************************************
 *
 *	This method copies the matrix `M` in a new matrix.
 *
 *	@param M Matrix: the matrix to be copied.
 *	@param m int: the number of rows of the matrix.
 *	@param n int: the number of columns of the matrix.
 *
 *	@return Matrix: the copy of the input matrix.
 *
 *************************************************************************/

Matrix copyMatrix(Matrix M, int m, int n){
	int i, j;           // counters
	Matrix C;           // the copied matrix

	C = allocMatrix(m, n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			C[i][j] = M[i][j];

	return C;
}

//
//  Algebraic Operation
//


/** multMV ****************************************************************
 *
 *	This method multiplies a `m x n` Matrix `A` for a `n` Vector `b` and
 *	 stores the result in a `m` Vector `x`.
 *
 *	@param A Matrix: the matrix.
 *	@param b Vector: the vector.
 *	@param m int: the number of rows of the matrix.
 *	@param n int: the number of columns of the matrix. It must be equal
 *	               to the number of elements in the vector.
 *	@param x Vector: the answer vector (will be filled).
 *
 *	@return NULL.
 *
 *************************************************************************/

void multMV(Matrix A, Vector b, int m, int n, Vector x){
	int i, j;           // counters
	double sum;         // temp variable

	for (i = 0; i < m; i++){
		sum = 0.0;
		for (j = 0; j < n; j++)
			sum += (A[i][j] * b[j]);
		x[i] = sum;
	}

	return ;
}


/** multMM ****************************************************************
 *
 *	This method multiplies a `m x n` Matrix `A` for a `n x k` Matrix `B`
 *	 and stores the result in a `m x k` Vector `x`.
 *
 *	@param A Matrix: the first matrix.
 *	@param B Matrix: the second matrix.
 *	@param m int: the number of rows of the first matrix.
 *	@param n int: the number of columns of the first matrix. It must be
 *	               equal to the number of rows of the second matrix.
 *	@param l int: the number of columns of the second matrix.
 *	@param X Matrix: the answer matrix (will be filled).
 *
 *	@return NULL.
 *
 *************************************************************************/

void multMM(Matrix A, Matrix B, int m, int n, int l, Matrix X){
	int i, j, k;        // counters
	double sum;         // temp variable

	for (i = 0; i < m; i++){
		for (j = 0; j < l; j++){
			sum = 0.0;
			for (k=0; k<n; k++)
				sum += (A[i][k] * B[k][j]);
			X[i][j] = sum;
		}
	}

	return ;
}

/** splitMatrix ***********************************************************
 *
 *	This method splits a square matrix `A` in three matrices respectively:
 *	 - `D` the inferior triangular part.
 *	 - `E` the diagonal part.
 *	 - `F` the superior triangular part.
 *
 *	@param A Matrix: the matrix to be splitted.
 *	@param n int: the order of the matrix.
 *	@param D Matrix: the inferior matrix (will be filled).
 *	@param E Matrix: the diagonal matrix (will be filled).
 *	@param F Matrix: the superior matrix (will be filled).
 *
 *	@return NULL.
 *
 *************************************************************************/

void splitMatrix(Matrix A, int n, Matrix D, Matrix E, Matrix F){
	int i, j;           // counters

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++){
			if (i > j) {
				D[i][j] = A[i][j];
				E[i][j] = 0.0;
				F[i][j] = 0.0;
			} else if (i < j) {
				D[i][j] = 0.0;
				E[i][j] = 0.0;
				F[i][j] = A[i][j];
			} else {
				D[i][j] = 0.0;
				E[i][j] = A[i][j];
				F[i][j] = 0.0;
			}
		}

	return ;

}


/** isDiagonallyDominant **************************************************
 *
 *	This method checks if the matrix `M` given in input is (strictly)
 *	 diagonally dominant, ie:
 *	```math
 *	|a_{i,i}| \geq \sum_{j \ne i} |a_{i, j}|    \qquad (<)
 *	```
 *
 *	@param M Matrix: the matrix.
 *	@param m int: the number of rows of `M`.
 *	@param n int: the number of columns of `M`.
 *
 *	@return int: exit-code
 *	  `0` : `M` is not diagonally dominant.
 *	  `1` : `M` is diagonally dominant.
 *	  `2` : `M` is strictly diagonally dominant.
 *
 *************************************************************************/

int isDiagonallyDominant(Matrix M, int m, int n){
	int ans = 2;        // is strictly diagonally
	int i, j;           // counters
	double acc;         // sum accumulator

	for (i = 0; i < m; i++){
		acc = - (2 * fabs(M[i][i]));
		for (j = 0; j < n; j++)
			acc += fabs(M[i][j]);
		if (acc > 0)
			return 0;
		if (acc == 0)
			ans = 1;
	}

	return ans;
}


/** matrixDefiniteness ****************************************************
 *
 *	This method evaluates the matrix `M` definiteness, i.e. if:
 *	```math
 *	x^T * M * x (\geq, >, <, \leq) 0
 *	```
 *
 *	@param M Matrix: the matrix.
 *	@param m int: the number of rows of `M`.
 *	@param n int: the number of columns of `M`.
 *
 *	@return int: exit-code
 *	  `-2` : `M` is negative definite.
 *	  `-1` : `M` is negative semi-definite.
 *	  ` 0` : `M` is not definite.
 *	  `+1` : `M` is positive semi-definite.
 *	  `+2` : `M` is positive definite.
 *
 *************************************************************************/

int matrixDefiniteness(Matrix M, int m, int n){

	return 0;
}


//
//  Print Operation
//


/** printMatrix ***********************************************************
 *
 *	This method prints a Matrix `M`.
 *
 *	@param M Matrix: the matrix to be printed.
 *	@param m int: the number of rows.
 *	@param n int: the number of columns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printMatrix(Matrix M, int m, int n){
	int i, j;           // counters
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			printf("\t"lfpf"", M[i][j]);
		ln;
	}
}


/** printQMatrix **********************************************************
 *
 *	This method prints a square Matrix `M`.
 *
 *	@param M Matrix: the matrix to be printed.
 *	@param n int: the number of rows/columns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printQMatrix(Matrix M, int n){
	printMatrix(M, n, n);
}


/** fprintMatrix **********************************************************
 *
 *	This method prints a Matrix `arg` of dimnesions `m \times n` over
 *	 the specified file `dest`.
 *
 *	@param dest char*: the destination file `.txt` (string path).
 *	@param arg Matrix: the matrix to be printed.
 *	@param m int: the number of rows.
 *	@param n int: the number of columns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void fprintMatrix(char *dest, Matrix arg, int m, int n){
	int i, j;           // counter
	FILE *fileP;        // output file pointer

	fileP = fopen(dest, "w");

	if (fileP == NULL) {
		printf("ERROR: can't open %s in writing mode.\n", dest);
		exit(1);
	}

	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			fprintf(fileP, "  "flfpf"", arg[i][j]);
		fprintf(fileP, "\n");
	}

	fclose(fileP);

	return ;
}


/** fprintQMatrix *********************************************************
 *
 *	This method prints a square Matrix `arg` of dimension `n` over
 *	 the specified file `dest`.
 *
 *	@param dest char*: the destination file `.txt` (string path).
 *	@param arg Matrix: the matrix to be printed.
 *	@param n int: the dimension of the matrix.
 *
 *	@return NULL.
 *
 *************************************************************************/

void fprintQMatrix(char *dest, Matrix arg, int n){
	return fprintMatrix(dest, arg, n, n);
}
