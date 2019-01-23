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
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 */


#include "an1.iteratives.h"

int jacobi(Matrix A, Vector b, int n, Vector x);


/** jacobi ****************************************************************
 *
 *	This
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known term vector.
 *	@param n int: the dimension of the matrix and of the vector.
 *	@param x Vector: the unknown terms vector.
 *
 *	@return int: exit-code:
 *	  `0` : success.
 *
 *************************************************************************/

int jacobi(Matrix A, Vector b, int n, Vector x){
	Matrix D = NULL;    // inferior triangular matrix
	Matrix E = NULL;    // diagonal matrix
	Matrix F = NULL;    // superior triangular matrix

	//splitMatrix(A, n, &D, &E, &F);

	return 0;
}
