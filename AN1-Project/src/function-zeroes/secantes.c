/*
 *  secantes.c
 *
 *  Created on: 6 dic 2018
 *      Author: Elia Onofri
 */


#include "an1.function-zeroes.h"

double exeSecantes(double (*f)(double));

/**
 * Secantes method is a Iterative method to compute the zero of a given
 *  function `f`. To do so, it evaluates the secant between the last
 *  point found `x` and the previous one `xp`.
 *
 * <p>
 *
 * This method follows the following formula:
 * ```math
 *   g(x) = x - p(x) * f(x),    p(x) = (x - xp) / (f(x) - f(xp))
 * ```
 *  using the secant angular coefficient as increaser.
 *
 * @param x double: first point;
 * @param xp double: second point;
 * @param e double: approx error needed;
 * @param f double *(double): pointer to the function.
 *
 * @return x: the zero found by the method.
 */
double secantes(double xp, double x, double e, double (*f)(double)){
	int counter = 0;
	double fx = f(x);
	double fxp = f(xp);

	while (fabs(fx) > e && fx != fxp && counter < MAX_ATTEMPTs) {
		x = x - fx * (x - xp) / (fx - fxp);
		fxp = fx;
		fx = f(x);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs) printf("No zeros were found within the first %d iterations with the required precision. The partial zero found is located at `%lf`.\n", counter, x);
	else if (fxp == fx) printf("The method failed (at step %d) as f(x) - f(xp) = 0", counter);
	else printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return x;
}

double exeSecantes(double (*f)(double)){
	double x0, x1, e;

	printf("Type in the first two points of the iterations and the error range: ");
	scanf("%lf %lf %lf", &x0, &x1, &e);

	return secantes(x0, x1, e, f);
}
