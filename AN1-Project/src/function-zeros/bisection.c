/*
 * bisection.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, "%lf %lf\n", x, fx);
 *	 MAX_ATTEMPTs
 */

#include "an1.function-zeros.h"

int bisection(double a, double b, double e, double (*f)(double));


/** bisection *************************************************************
 *
 *	Bisection method is a Iterative method to compute the zero of a given
 *	 function `f`. To do so, it needs a left `a` and a right `b` element
 *	 to start from.
 *	It evaluates the medium point and assign it either to the left or
 *	 to the right margin so that it has the same sign.
 *	It continue doing so till the minimum error `e` is reached.
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/bisection.txt`
 *
 *	@param a double: left margin.
 *	@param b double: right margin.
 *	@param e double: max error range.
 *	@param f double *(double): pointer to the function.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f(a)` and `f(b)` are concordant.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int bisection(double a, double b, double e, double (*f)(double)){
	double c = a;       // mid point
	int counter = 0;    // iteration counter
	FILE *fileP;        // output file pointer

	fileP = fopen("results/function-zeros/bisection.txt", "w");

	if (f(a) * f(b)>=0) {
		if (f(a) == 0){
			printf("The function has a `0` in %lf", a);
			fprintPoint(fileP, a, 0.0);
			return a;
		}
		if (f(b) == 0){
			printf("The function has a `0` in %lf", b);
			fprintPoint(fileP, b, 0.0);
			return b;
		}
		printf("ERROR: f(a)*f(b) > 0!\n\n");
		return 0;
	}

	while (fabs(b-a) > e && fabs(f(c)) > e && counter < MAX_ATTEMPTs) {
		c = (a+b)/2;
		fprintPoint(fileP, c, f(c));
		if (f(a)*f(c) > 0) a = c;
		else b = c;
		counter++;
	}
	if (counter >= MAX_ATTEMPTs){
		printf("No zeros were found within the first %d iterations with the required precision.\n", counter);
		printf("The partial zero found is located at `%lf`.\n", c);
		return 2;
	}
	else
		printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", c, counter, e);
	return 0;
}
