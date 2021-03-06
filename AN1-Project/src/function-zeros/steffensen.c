/*
 * steffensen.c
 *
 *  Created on: 6 dic 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, flfpf" "flfpf"\n", x, fx);
 *	 MAX_ATTEMPTs
 */


#include "an1.function-zeros.h"

int steffensen(double x, double e, double (*f)(double));


/** steffensen ************************************************************
 *
 *	Steffensen method is a Iterative method to compute the zero of a given
 *	 function `f`. To do so, it only needs a initial point `x0`.
 *
 *	This method follows the following formula:
 *	```math
 *	  g(x) = x - p(x) * f(x),    p(x) = f(x) / (f(x) - f(x - f(x)))
 *	```
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/steffensen.txt`
 *	and evaluates a scheme for the function `f` in a file called:
 *	 `results/function-plot/functionData.txt`
 *
 *	@param x double: initial point `x0`;
 *	@param e double: approx error needed;
 *	@param f double *(double): pointer to the function.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f'(x) = 0` during computation.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int steffensen(double x, double e, double (*f)(double)){
	int counter = 0;    // counter
	double fx;          // current point function value
	double ffx;         // steffensen point function value
	double min, max;    // minimum and maximum points for the representation
	FILE *fileP;        // output file pointer

	fileP = fopen("results/function-zeros/steffensen.txt", "w");

	fx = f(x);
	ffx = f(x + fx);
	min = x - 1;
	max = x + 1;

	fprintPoint(fileP, x, fx);

	while (fabs(fx) > e && ffx != fx && counter < MAX_ATTEMPTs) {
		x = x - ((fx * fx) / (ffx - fx));
		fx = f(x);
		ffx = f(x + fx);
		fprintPoint(fileP, x, fx);
		if (x < min)
			min = x - 1;
		else if (x > max)
			max = x + 1;
		counter++;
	}

	fclose(fileP);
	fprintFunction(f, min, max);

	if (ffx == fx){
		printf("The method failed (at step %d, x = "lfpf") as f(x - f(x)) - f(x) = 0", counter, x);
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

