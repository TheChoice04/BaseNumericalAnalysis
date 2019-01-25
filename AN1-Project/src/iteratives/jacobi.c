/*
 * jacobi.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 MAX_ATTEMPTs
 */


#include "an1.iteratives.h"

int jacobi(Matrix A, Vector b, int n, Vector x, double err, int p);


/** jacobi ****************************************************************
 *
 *	This
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known term vector.
 *	@param n int: the dimension of the matrix and of the vector.
 *	@param x Vector: the unknown terms vector.
 *	@param err double: max error range.
 *	@param p int: norm counter.
 *
 *	@return int: exit-code:
 *	  `0` : success.
 *
 *************************************************************************/

int jacobi(Matrix A, Vector b, int n, Vector x, double err, int p){
	/*
	Matrix D = NULL;    // inferior triangular matrix
	Matrix E = NULL;    // diagonal matrix
	Matrix F = NULL;    // superior triangular matrix
	Matrix Bj = NULL;   // updating matrix
	Vector cj = NULL;   // updating vector

	D = allocQMatrix(n);
	E = allocQMatrix(n);
	F = allocQMatrix(n);

	splitMatrix(A, n, D, E, F);
	*/

	int i, j, counter;  // counters
	Matrix Bj = NULL;   // updating matrix
	Vector cj = NULL;   // updating vector
	double norm;        // error norm

	Bj = allocQMatrix(n);
	cj = allocVector(n);

	// Basis Construction
	for (i = 0; i < n; i++){
		if (A[i][i] == 0.0){
			printf("ERROR: The matrix must have non-zero value on its diagonal.");
		}
		for (j = 0; j < n; j++)
			if (i == j)
				Bj[i][j] = 0.0;
			else
				Bj[i][j] = - A[i][j]/A[i][i];
		cj[i] = b[i] / A[i][i];
	}

	counter = 0;
	norm = evalSystemError();
	while (norm < err && counter < MAX_ATTEMPTs){
		//ToDo
		counter++;
	}




	return 0;
}
