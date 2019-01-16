/*
 * lagrange.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */


#include "an1.interpolation.h"

/**
 * This method generate and evaluate (over `dpts` points) the interpolate (from a Lagrange point of view) of the `*f` function
 *  over the `knot` vector, given in input.
 * To do so it creates the Lagrange base defined as:
 * ```math
 * 	L_i(x) = \prod_{j \ne i}\frac{x-x_j}{x_i-x_j}
 * ```
 * and evaluates the interpolate:
 * ```math
 * \Pi_n(x) = \sum_{i=0}^n f(x_i) \cdot L_i(x)
 * ```
 * It then save the results of the interpolation in `interpolation.lagrange.txt` with the following structure:
 *  x    \Pi(x)    f(x)    delta
 *
 * @param f double *(double): The real function;
 * @param npts int: number of knots;
 * @param knot Vector: vector of the knots;
 * @param dpts int: number of data points;
 * @param a float: left margin of the range;
 * @param b float: right margin of the range.
 */

void lagrange(double (*f)(double), int npts, Vector knot, int dpts, float a, float b){
	float step = (b-a)/(dpts-1);
	float x = a, acc, L, err, fx;
	int i, j, k;
	int n = npts-1;
	Vector knotVal = allocVector(npts);
	FILE *file = fopen("interpolation.lagrange.txt", "w");

	if (file == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}

	if (dpts <= 0) {
		printf("ERROR: no data points selected.\n");
		exit(1);
	}

	for (i = 0; i <= n; i++){
		knotVal[i] = f(knot[i]);
	}

	for (k = 0; k <= dpts; k++){
		acc = 0;
		for (i = 0; i <= n; i++){
			L = 1;
			for (j = 0; j <= n; j++){
				if (i != j) {
					L = L * (x - knot[j])/(knot[i] - knot[j]);
				}
			}
			acc += (L * knotVal[i]);
		}
		fx = f(x);
		err = fabs(fx-acc);
		fprintf(file, "%lf %lf %lf %lf", x, acc, fx, err);
		x += step;
	}

	fclose(file);

	return ;
}

void exeLagrange(double (*f)(double), int npts, Vector knot, int dpts, float a, float b){
	lagrange(f, npts, knot, dpts, a, b);
}
