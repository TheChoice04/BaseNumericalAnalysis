/*
 * newtonInterpolate.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Vector -> double*
 *	 Matrix -> double**
 */


#include "an1.polynomialApproximation.h"

int newtonInterpolate(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b);


/** newtonInterpolate *****************************************************
 *
 *	This method generate and evaluate (over `dpts` points) the interpolate
 *	 (from a Newton point of view) of the `*f` function over the `knot`
 *	 vector, given in input and their value `knotVal`.
 *	To do so it creates the Newton divided differences table fefined as:
 *	```math
 *		dd[i][j] =
 *		\begin{cases}
 *			\frac{dd[i+1, j] - dd[i, j-1]}{x[j] - x[i]}
 *				&	\mbox{if } i > j\\
 *			x[i]
 *				&	\mbox{if } i = j\\
 *			0
 *				&	\mbox{if } i < j
 *		\end{cases}
 *	```
 *	 and evaluates the interpolate:
 *	```math
 *		\Pi_n(x) = \sum_{i=0}^n dd[0, i] \cdot \prod_{j=0}^{i-1} (x - x[i])
 *	```
 *	It then save the results of the interpolation in the file:
 *	 `results/interpolation/newton_interpolate.txt`
 *	with the following structure:
 *		x    \Pi(x)    f(x)    delta
 *
 *	and saves the divided differences table in the file:
 *	 `results/interppolynomialApproximationolation/divided_differences.txt`
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

int newtonInterpolate(double (*f)(double), int npts, Vector knot, Vector knotVal, int dpts, float a, float b){
	int i, j, k;        // counters
	float step;         // step between data points
	float x = a;        // current data point
	float acc;          // accumulator
	float prod;         // productory
	float err;          // data point distance
	float fx;           // real value on x
	FILE *fileP;        // output file pointer
	Matrix dd;          // divided differences table

	step = (b - a)/(dpts - 1);

	if (dpts <= 0) {
		printf("ERROR: no data points selected.\n");
		return 1;
	}

	fileP = fopen("results/polynomialApproximation/newton_interpolate.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/polynomialApproximation/newton_interpolate.txt` in writing mode.\n");
		exit(1);
	}

	dd = allocQMatrix(npts);

	// initialization of divided differences

	for (i = 0; i < npts; i++)
		dd[i][i] = knotVal[i];

	// evaluation of divided differences

	for (j = 1; j < npts; j++){
		for (i = 0; i < npts - j; i++){
			dd[i][i+j] = (dd[i+1][i+j] - dd[i][i+j-1]) / (knot[i+j] - knot[i]);
			//printf("dd[%d][%d] = "lfpf"\n", i, i+j, dd[i][i+j]);
		}
	}

	fprintMatrix("results/polynomialApproximation/divided_differences.txt", dd, npts, npts);

	// evaluation of the data points
	for (k = 0; k < dpts; k++){
		acc = 0;
		prod = 1;
		for (j = 0; j < npts; j++){
			acc = acc + dd[0][j] * prod;
			prod = prod * (x - knot[j]);
		}
		fx = f(x);
		err = fabs(fx - acc);
		fprintf(fileP, ""flfpf" "flfpf" "flfpf" %10le\n", x, acc, fx, err);
		x += step;
	}

	fclose(fileP);
	free(dd);

	return 0;
}
