/*
 * least-squares.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
 */


#include "an1.regression-analysis.h"

int leastSquare(Matrix P, int n, int ord);
int leastSquareLine(Matrix P, int n);


/** leastSquare ***********************************************************
 *
 *	This method evaluates the polynomial of order `ord` across the `n`
 *	 points such that its distance is as minor as possible.
 *
 *	@param P Matrix: points matrix `n \times 2`
 *	@param n int: number of points
 *	@param ord int: order of the polynomial
 *
 *	@return int exit-code:
 *      `0` : Correct outcome.
 *      `1` : Unexpected error.
 *      `2` : `ord` < 1.
 *      `3` : method not yet encoded.
 *
 *************************************************************************/

int leastSquare(Matrix P, int n, int ord){

	if (ord < 1){
		printf("ERROR: the order must be strictly positive.\n");
		return 2;
	} else if (ord == 1)
		return leastSquareLine(P, n);

	return 3;
}


/** leastSquareLine *******************************************************
 *
 *	This method evaluates the straight line across the `n` points
 *	 such that its distance is as minor as possible.
 *
 *	@param P Matrix: points matrix `n \times 2`
 *	@param n int: number of points
 *
 *	@return int exit-code:
 *      `0` : Correct outcome.
 *      `1` : Unespected error.
 *
 *************************************************************************/

int leastSquareLine(Matrix P, int n){



	return 0;
}

