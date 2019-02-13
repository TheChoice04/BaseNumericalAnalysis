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
 *	It also write the results on the file:
 *	 `results/regression-analysis/leastSquaresLine`
 *	in the format:
 *	 `x y ya err
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
	int i;              // counter
	double x, y;        // points values
	double ya;          // y approximation
	double A00 = n;     // A[0,0]
	double A01 = 0.0;   // A[1,0] = A[0,1]
	double A11 = 0.0;   // A[1,1]
	double b0 = 0.0;    // b[0]
	double b1 = 0.0;    // b[1]
	double det;         // determinant of the matrix
	double m;           // angular coefficient of line
	double q;           // known term of the line
	double res = 0.0;   // residue
	double err;         // control point errors
	double min, max;    // min and max of the representation
	FILE *fileP;        // output file pointer

	min = P[0][0];
	max = min;

	for (i = 0; i < n; i++){
		x = P[i][0];
		y = P[i][1];
		A01 += x;
		A11 += x*x;
		b0 += y;
		b1 += x*y;

		if (min > x)
			min = x;
		else if (max < x)
			max = x;
	}

	det = (A00 * A11) - (A01 * A01);
	q = ((b0 * A11) - (A01 * b1)) / det;
	m = ((A00 * b1) - (b0 * A01)) / det;

	fileP = fopen("results/regression-analysis/leastSquaresLine.txt", "w");

	if (fileP == NULL){
		printf("ERROR: can't open `results/regression-analysis/leastSquaresLine.txt` in writing mode.");
		exit(1);
	}

	for (i = 0; i < n; i++){
		x = P[i][0];
		y = P[i][1];
		ya = (m * x) + q;

		err = fabs(ya - y);
		res += (err * err);

		fprintf(fileP, ""flfpf" "flfpf" "flfpf" %10le\n", x, ya, y, err);

	}

	fclose(fileP);

	res *= 0.5;

	printf("The points could be approximated by the straight line:\n");
	printf("\ty = "lfpf"x + "lfpf"\n", m, q);
	printf("And its residue is %10le.\n", res);


	return 0;
}

