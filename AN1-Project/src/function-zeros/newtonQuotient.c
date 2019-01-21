/*
 * newtonQuotient.c
 *
 *  Created on: 6 dic 2018
 *      Author: Elia Onofri
 */

#include "an1.function-zeros.h"

int newtonQuotient(double x, double h, double e, double (*f)(double));


/** newtonQuotient ********************************************************
 *
 *	Newton Quotient method is a Iterative method to compute the zero
 *	 of a given function `f`. To do so, it evaluates the Difference
 *	 Quotient with a fixed increment value `h`.
 *
 *	This method follows the following formula:
 *	```math
 *	  g(x) = x - p(x) * f(x),    p(x) = h / (f(x) - f(x + h))
 *	```
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/newtonQuotient.txt`
 *
 *	@param x double: initial point.
 *	@param h double: increment value.
 *	@param e double: max error range.
 *	@param f double *(double): pointer to the function.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : found a zero during the computation for the quotien.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int newtonQuotient(double x, double h, double e, double (*f)(double)){
	int counter = 0;    // counter
	double fx;          // current point function value
	float fxh;          // current point derivative value
	FILE *fileP;        // output file pointer

	fileP = fopen("results/function-zeros/newtonQuotient.txt", "w");

	fx = f(x);
	fxh = f(x + h);

	fprintPoint(fileP, x, fx);

	while (fabs(fx) > e && fx != fxh && counter < MAX_ATTEMPTs) {
		x = x - fx * h / (fxh - fx);
		fxh = f(x + h);
		fx = f(x);
		fprintPoint(fileP, x, fx);
		counter++;
	}

	if (fxh == fx){
		printf("The method failed (at step %d, x = %lf) as the quotient was zero.", counter, x);
		return 1;
	}
	if (counter >= MAX_ATTEMPTs){
		printf("No zeros were found within the first %d iterations with the required precision.\n", counter);
		printf("The partial zero found is located at `%lf`.\n", x);
		return 2;
	}
	printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return 0;
}
