/*
 * newton.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, flfpf" "flfpf"\n", x, fx);
 *	 MAX_ATTEMPTs
 */


#include "an1.function-zeros.h"

int newton(double x, double e, double (*f)(double), double (*f1)(double));


/** newton ****************************************************************
 *
 *	Newton Method is an iterative method to compute a zero of a given
 *	 function `f` by the knowledge of its first derivative `f1`.
 *	Starting from a nearby point `x0`, the method collides on the zero if:
 *	  - convex  increasing and `x0 > x`
 *	  - concave increasing and `x0 < x`
 *	  - convex  decreasing and `x0 < x`
 *	  - concave decreasing and `x0 > x`
 *
 *	This method follows the following formula:
 *	```math
 *	  g(x) = x - p(x) * f(x),    p(x) = 1 / f'(x)
 *	```
 *	 using the derivative as increaser.
 *	The method is fast but need to know the derivative of the function.
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/newton.txt`
 *
 *	Moreover the function builds a file to display the points called:
 *	 `results/function-zeros/newton_display.txt`
 *	and evaluates a scheme for the function `f` in a file called:
 *	 `results/function-plot/functionData.txt`
 *
 *	@param x double: initial point of the function `x0`.
 *	@param e double: max error range.
 *	@param f double *(double): pointer to the function.
 *	@param f1 double *(double): pointer to the first derivative of `f`.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f'(x) = 0` during computation.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int newton(double x, double e, double (*f)(double), double (*f1)(double)){
	int counter = 0;    // counter
	float fx;           // current point function value
	float f1x;          // current point derivative value
	double min, max;    // minimum and maximum points for the representation
	FILE *fileP;        // output file pointer
	FILE *filePd;       // diplay file pointer

	fileP = fopen("results/function-zeros/newton.txt", "w");
	filePd = fopen("results/function-zeros/newton_display.txt", "w");

	fx = f(x);
	f1x = f1(x);
	min = x - 1;
	max = x + 1;

	fprintPoint(fileP, x, fx);
	fprintPoint(filePd, x, 0.0);
	fprintPoint(filePd, x, fx);

	while (fabs(fx) > e && counter < MAX_ATTEMPTs && f1x != 0){
		x = x - fx/f1x;
		fx = f(x);
		f1x = f1(x);

		fprintPoint(fileP, x, fx);
		fprintPoint(filePd, x, 0.0);
		fprintPoint(filePd, x, fx);
		if (x < min)
			min = x - 1;
		else if (x > max)
			max = x + 1;
		counter++;
	}

	fclose(fileP);
	fclose(filePd);
	fprintFunction(f, min, max);

	if (f1x == 0){
		printf("The method failed (at step %d, x = "lfpf") as the derivative was zero.", counter, x);
		return 1;
	}

	if (counter >= MAX_ATTEMPTs){
		printf("No zeros were found within the first %d iterations with the required precision.\n", counter);
		printf("The partial zero found is located at `"lfpf"`.\n", x);
		return 2;
	}
	printf("The function has a zero in `"lfpf"` (found in %d iteration) with a maximum error of `%10le`.\n", x, counter, e);

	return 0;
}
