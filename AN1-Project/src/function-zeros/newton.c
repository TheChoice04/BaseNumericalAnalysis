/*
 *  newton.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 */


#include "an1.function-zeros.h"

/**
 * Newton Method is an iterative method to compute a zero of a given
 *  function `f` by the knowledge of its first derivative `f1`. Starting from
 *  a nearby point `x0`, the method collides on the zero if:
 *   - convex  increasing and `x0 > x`
 *   - concave increasing and `x0 < x`
 *   - convex  decreasing and `x0 < x`
 *   - concave decreasing and `x0 > x`
 *
 * <p>
 *
 * This method follows the following formula:
 * ```math
 *   g(x) = x - p(x) * f(x),    p(x) = 1 / f'(x)
 * ```
 *  using the derivative as increaser.
 * The method is fast but need to know the derivative of the given function.
 *
 * @param x double: initial point of the function `x0`
 * @param e double: max error expected
 * @param f double *(double): pointer to the function
 * @param f1 double *(double): pointer to the first derivate of `f`
 *
 * @return x double: an approx of the zero of the function.
 */

double newton(double x, double e, double (*f)(double), double (*f1)(double)){
	float fx = f(x);
	int counter = 0;

	while (fabs(fx) > e && counter<MAX_ATTEMPTs){
		x = x - fx/f1(x);
		fx = f(x);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs) printf("No zeros were found within the first %d iterations with the required precision. The partial zero found is located at `%lf`.\n", counter, x);
	else printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return x;
}

double exeNewton(double (*f)(double), double (*f1)(double)){
	double x, e;

	printf("Type in the initial point and the error range: ");
	scanf("%lf %lf", &x, &e);

	return newton(x, e, f, f1);
}
