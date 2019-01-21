/*
 *  newton.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) fprintf(p, "%lf %lf\n", x, fx);
 *	 MAX_ATTEMPTs
 */


#include "an1.function-zeros.h"

int newton(double x, double e, double (*f)(double), double (*f1)(double));


/** newton ****************************************************************
 *
 * Newton Method is an iterative method to compute a zero of a given
 *  function `f` by the knowledge of its first derivative `f1`.
 * Starting from a nearby point `x0`, the method collides on the zero if:
 *   - convex  increasing and `x0 > x`
 *   - concave increasing and `x0 < x`
 *   - convex  decreasing and `x0 < x`
 *   - concave decreasing and `x0 > x`
 *
 * This method follows the following formula:
 * ```math
 *   g(x) = x - p(x) * f(x),    p(x) = 1 / f'(x)
 * ```
 *  using the derivative as increaser.
 * The method is fast but need to know the derivative of the function.
 *
 * The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/newton.txt`
 *
 * @param x double: initial point of the function `x0`.
 * @param e double: max error range.
 * @param f double *(double): pointer to the function.
 * @param f1 double *(double): pointer to the first derivative of `f`.
 *
 * @return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f'(x) = 0` during computation.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int newton(double x, double e, double (*f)(double), double (*f1)(double)){
	int counter = 0;    // counter
	float fx = f(x);    // current point function value
	float f1x = f1(x);  // current point derivative value
	FILE *fileP;        // output file pointer

	fileP = fopen("results/function-zeros/newton.txt", "w");

	fprintPoint(fileP, x, fx);

	while (fabs(fx) > e && counter < MAX_ATTEMPTs && f1x != 0){
		x = x - fx/f1x;
		fx = f(x);
		f1x = f1(x);
		fprintPoint(fileP, x, fx);
		counter++;
	}

	if (f1x == 0){
		printf("During computation a zero for the derivative was found at %lf.", x);
		return 1;
	}

	if (counter >= MAX_ATTEMPTs){
		printf("No zeros were found within the first %d iterations with the required precision.\n", counter);
		printf("The partial zero found is located at `%lf`.\n", x);
		return 2;
	}
	else
		printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return x;
}
