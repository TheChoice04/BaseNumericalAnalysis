/*
 *  chord.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia Onofri
 */

#include "an1.iteratives.h"

double exeChord(double (*f)(double));

/**
 * Chord method is a Iterative method to compute the zero of a given
 *  function `f`. To do so, it needs a left `a` and a right `b` element to
 *  initialize the chord parameter and a point to start from `x0`.
 *
 * <p>
 *
 * This method follows the following formula:
 * ```math
 *   g(x) = x - p * f(x),    p = (b - a) / (f(b) - f(a))
 * ```
 *  using the chord (fixed) angular coefficient as increaser.
 *
 * @param a double: left margin;
 * @param b double: right margin;
 * @param x double: initial point `x0`;
 * @param e double: approx error needed;
 * @param f double *(double): pointer to the function.
 *
 * @return x: the zero found by the method.
 */
double chord(double a, double b, double x, double e, double (*f)(double)){
	int counter = 0;
	double fx = f(x);

	if (f(a) - f(b) == 0.0){
		printf("ERROR: The values of f(a) and f(b) are equals. Chord method not valid.\n");
		return x;
	} else if (a == b) {
		printf("ERROR: The values of a and b must be different.\n");
		return x;
	} else if (a>b){
		float c;
		c = a;
		a = b;
		b = c;
	}

	double alpha = (b - a)/(f(b) - f(a));

	while (fabs(fx) > e && counter < MAX_ATTEMPTs) {
		x = x - alpha*fx;
		fx = f(x);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs) printf("No zeros were found within the first %d iterations with the required precision. The partial zero found is located at `%lf`.\n", counter, x);
	else printf("The function has a zero in `%lf` (found in %d iteration) with a maximum error of `%lf`.\n", x, counter, e);

	return x;
}

double exeChord(double (*f)(double)){
	double a, b, x, e;

	printf("Type in the left initialization, the right one, the initial point and the error range: ");
	scanf("%lf %lf %lf %lf", &a, &b, &x, &e);

	return chord(a, b, x, e, f);
}
