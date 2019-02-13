/*
 * lagrange.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
 */


#include "an1.polynomialApproximation.h"

int lagrange(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b);


/** lagrange **************************************************************
 *
 *	This method generate and evaluate (over `dpts` points) the interpolate
 *	 (from a Lagrange point of view) of the `*f` function over the `knot`
 *	 vector, given in input.
 *	To do so it creates the Lagrange base defined as:
 *	```math
 *		L_i(x) = \prod_{j \ne i}\frac{x-x_j}{x_i-x_j}
 *	```
 *	 and evaluates the interpolate:
 *	```math
 *		\Pi_n(x) = \sum_{i=0}^n f(x_i) \cdot L_i(x)
 *	```
 *	It then save the results of the interpolation in
 *	 `interpolation.lagrange.txt` with the following structure:
 *		x    \Pi(x)    f(x)    delta
 *
 *	@param f double *(double): The real function.
 *	@param npts int: number of knots.
 *	@param knot Vector: vector of the knots.
 *	@param knotVal Vector: vector of the knot values.
 *	@param dpts int: number of data points.
 *	@param a float: left margin of the range.
 *	@param b float: right margin of the range.
 *
 *	@return int exit-code:
 *      `0` : Correct outcome.
 *      `1` : No data points selected.
 *
 *************************************************************************/

int lagrange(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b){
	int i, j, k;        // counters
	int n = npts-1;     // order of the interpolate
	float step;         // step between data points
	float x = a;        // current data point
	float acc;          // accumulator
	float L;            // Lagrange Basis
	float err;          // data point distance
	float fx;           // real value on x
	FILE *fileP;        // output file pointer

	step = (b - a)/(dpts - 1);

	if (dpts <= 0) {
		printf("ERROR: no data points selected.\n");
		return 1;
	}

	fileP = fopen("results/polynomialApproximation/lagrange_interpolate.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/polynomialApproximation/lagrange_interpolate.txt` in writing mode.\n");
		exit(1);
	}

	for (k = 0; k < dpts; k++){
		acc = 0;
		for (i = 0; i <= n; i++){
			L = 1;
			for (j = 0; j <= n; j++){
				if (i != j) {
					L = L * (x - knot[j])/(knot[i] - knot[j]);
				}
			}
			acc = acc + (L * knotVal[i]);
		}
		fx = f(x);
		err = fabs(fx-acc);
		fprintf(fileP, ""flfpf" "flfpf" "flfpf" %10le\n", x, acc, fx, err);
		x += step;
	}

	fclose(fileP);

	return 0;
}
