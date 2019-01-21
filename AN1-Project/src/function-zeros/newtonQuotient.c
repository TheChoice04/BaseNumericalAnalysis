/*
 *  newtonQuotient.c
 *
 *  Created on: 6 dic 2018
 *      Author: Elia Onofri
 */

#include "an1.function-zeros.h"

double exeNewtonQuotient(double (*f)(double));

/**
 * Newton Quotient method is a Iterative method to compute the zero of a given
 *  function `f`. To do so, it evaluates the Difference Quotient with a fixed
 *  increment value `h`.
 *
 * <p>
 *
 * This method follows the following formula:
 * ```math
 *   g(x) = x - p(x) * f(x),    p(x) = h / (f(x) - f(x + h))
 * ```
 *
 * @param x double: initial point;
 * @param h double: increment value;
 * @param e double: approx error needed;
 * @param f double *(double): pointer to the function.
 *
 * @return x: the zero found by the method.
 */
double newtonQuotient(double x, double h, double e, double (*f)(double)){
	int counter = 0;
	double fx = f(x);
	double fxh = f(x + h);

	while (fabs(fx) > e && fx != fxh && counter < MAX_ATTEMPTs) {
		x = x - fx * h / (fx - fxh);
		fxh = f(x + h);
		fx = f(x);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs) printf("No zeros were found within the first %d iterations with the required precision. The partial zero found is located at `%lf`.\n", counter, x);
	else if (fxh == fx) printf("The method failed (at step %d) as f(x) - f(x + h) = 0", counter);
	else printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return x;
}

double exeNewtonQuotient(double (*f)(double)){
	double x, h, e;

	printf("Type in the initial point, the fixed increment and the error range: ");
	scanf("%lf %lf %lf", &x, &h, &e);

	return newtonQuotient(x, h, e, f);
}
