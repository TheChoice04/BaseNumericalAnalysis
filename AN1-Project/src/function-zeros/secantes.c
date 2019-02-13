/*
 * secantes.c
 *
 *  Created on: 6 dic 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, flfpf" "flfpf"\n", x, fx);
 *	 MAX_ATTEMPTs
 */


#include "an1.function-zeros.h"

int secantes(double xp, double x, double e, double (*f)(double));


/** secantes **************************************************************
 *
 *	Secantes method is a Iterative method to compute the zero of a given
 *	 function `f`. To do so, it evaluates the secant between the last
 *	 point found `x` and the previous one `xp`.
 *
 *	This method follows the following formula:
 *	```math
 *	  g(x) = x - p(x) * f(x),    p(x) = (x - xp) / (f(x) - f(xp))
 *	```
 *	 using the secant angular coefficient as increaser.
 *
 *	The method also print the sequence of points found on a file called:
 *	 `results/function-zeros/secantes.txt`
 *
 *	Moreover the function builds a file to display the points called:
 *	 `results/function-zeros/secantes_display.txt`
 *	and evaluates a scheme for the function `f` in a file called:
 *	 `results/function-plot/functionData.txt`
 *
 *	@param x double: first point;
 *	@param xp double: second point;
 *	@param e double: max error range;
 *	@param f double *(double): pointer to the function.
 *
 *	@return int exit-code:
 *	  `0` : correct output (zero found).
 *	  `1` : `f'(x) = 0` during computation.
 *	  `2` : iteration number have overflow (no zero found).
 *
 *************************************************************************/

int secantes(double xp, double x, double e, double (*f)(double)){
	int counter = 0;    // counter
	double fx;          // current point function value
	double fxp;         // last point function value
	double xt;          // temp x value during upgrade
	double min, max;    // minimum and maximum points for the representation
	FILE *fileP;        // output file pointer
	FILE *filePd;       // diplay file pointer

	fileP = fopen("results/function-zeros/secantes.txt", "w");
	filePd = fopen("results/function-zeros/secantes_display.txt", "w");

	fx = f(x);
	fxp = f(xp);
	if (x < xp){
		min = x - 1;
		max = xp + 1;
	} else {
		min = xp - 2;
		max = x + 2;
	}

	fprintPoint(fileP, xp, fxp);
	fprintPoint(fileP, x, fx);

	fprintPoint(filePd, xp, 0.0);
	fprintPoint(filePd, xp, fxp);
	fprintPoint(filePd, x, fx);
	fprintPoint(filePd, x, 0.0);
	fprintPoint(filePd, x, fx);


	while (fabs(fx) > e && fx != fxp && counter < MAX_ATTEMPTs) {
		xt = x - fx * (x - xp) / (fx - fxp);
		xp = x;
		fxp = fx;
		x = xt;
		fx = f(x);

		fprintPoint(fileP, x, fx);
		fprintPoint(filePd, x, 0.0);
		fprintPoint(filePd, x, fx);
		fprintPoint(filePd, xp, fxp);
		if (x < min)
			min = x - 1;
		else if (x > max)
			max = x + 1;
		counter++;
	}

	fclose(fileP);
	fclose(filePd);
	fprintFunction(f, min, max);

	if (fxp == fx){
		printf("The method failed (at step %d, x = "lfpf", xp = "lfpf") as f(x) - f(xp) = 0.\n", counter, x, xp);
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

