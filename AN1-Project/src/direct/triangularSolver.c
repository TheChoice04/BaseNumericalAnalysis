/*
 * triangularSolver.c
 *
 *  Created on: 19 gen 2019
 *      Author: Elia
 *
 **
 *	Macros used:
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 ERR
 */


#include "an1.direct.h"

int triSupSolver(Matrix A, Vector b, int m, int n, Vector x);
int triInfSolver(Matrix A, Vector b, int m, int n, Vector x);


/** triSupSolver **********************************************************
 *
 *	This method solve a triangular system given in input under the form
 *	 of a coefficient matrix and a known term vector.
 *
 *	@param A Matrix: the coefficient matrix (will be modified).
 *	@param b Vector: the known terms vector (will be modified).
 *	@param m int: the number of rows (equations).
 *	@param n int: the number of columns (unknown).
 *	@param x Vector: the unknown vector (will be filled up);
 *
 *	@return int exit-code:
 *	  `0` compatible;
 *	  `1` not compatible.
 *
 *************************************************************************/

int triSupSolver(Matrix A, Vector b, int m, int n, Vector x){
	int i, j;           // counters
	double acc;         // accumulator

	/*
	for (i = 0; i < n; i++){
		x[i] = 0.0;
	}
	*/

	// if m > n
	for (i = n; i < m; i++){
		if (b[i] >= ERR){
			printf("The system is not compatible.\n");
			return 1;
		}

	}

	for (i = n-1; i >= 0; i--){
		acc = b[i];
		for (j = i+1; j < n; j++)
			acc = acc - (A[i][j] * x[j]);
		acc = acc / A[i][i];
		x[i] = acc;
	}

	return 0;
}

int triInfSolver(Matrix A, Vector b, int m, int n, Vector x){
	return 0;
}
