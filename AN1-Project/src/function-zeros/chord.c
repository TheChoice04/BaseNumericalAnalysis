/*
 * chord.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) fprintf(p, "%lf %lf\n", x, fx)
 *	 MAX_ATTEMPTs
 */

#include "an1.function-zeros.h"

int chord(double a, double b, double x, double e, double (*f)(double));


/** chord *****************************************************************
 *
 *	Chord method is a Iterative method to compute the zero of a given
 *	 function `f`. To do so, it needs a left `a` and a right `b` element
 *	 to initialize the chord parameter and a point to start from `x0`.
 *
 *	This method follows the following formula:
 *	```math
 *	  g(x) = x - p * f(x),    p = (b - a) / (f(b) - f(a))
 *	```
 *	 using the chord (fixed) angular coefficient as increaser.
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/chord.txt`
 *
 *	@param a double: left margin.
 *	@param b double: right margin.
 *	@param x double: initial point `x0`.
 *	@param e double: max error range.
 *	@param f double *(double): pointer to the function.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f(a)` and `f(b)` are equals.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int chord(double a, double b, double x, double e, double (*f)(double)){
	int counter = 0;    // iteration counter
	double fx = f(x);   // current point function value
	double alpha;       // angular coefficient of the chord.
	FILE *fileP;        // output file pointer

	fileP = fopen("results/function-zeros/chord.txt", "w");

	if (f(a) - f(b) == 0.0){
		printf("ERROR: The values of f(a) and f(b) are equals. Chord method not valid.\n");
		return 1;
	}

	fprintPoint(fileP, x, fx);

	alpha = (b - a)/(f(b) - f(a));

	while (fabs(fx) > e && counter < MAX_ATTEMPTs) {
		x = x - (alpha * fx);
		fx = f(x);
		fprintPoint(fileP, x, fx);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs){
		printf("No zeros were found within the first %d iterations with the required precision.\n", counter);
		printf("The partial zero found is located at `%lf`.\n", x);
		return 2;
	}
	else
		printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return 0;
}
