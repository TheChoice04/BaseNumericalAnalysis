/*
 * newton.c
 *
 *  Created on: 22 nov 2018
 *      Author: Elia
 */


#include "an1.iteratives.h"

/**
 * Newton Method is an iterative method to compute a zero of a given
 *  function `f` by the knowledge of its first derivate. Starting from
 *  a nearby point, the method collides on the zero if:
 *   - convex  increasing and `x0 > x`
 *   - concave increasing and `x0 < x`
 *   - convex  decreasing and `x0 < x`
 *   - concave decreasing and `x0 > x`
 *
 * @param x double: starting point of the function
 * @param e double: max error expected
 * @param f double *(double): pointer to the function
 * @param f1 double *(double): pointer to the first derivate of `f`
 *
 * @return x double: an approx of the zero of the function.
 */

double newton(double x, double e, double (*f)(double), double (*f1)(double)){
	float d = f(x);
	int counter = 0;

	while (fabs(d) > e && counter<MAX_ATTEMPTs){
		x = x - d/f1(x);
		d = f(x);
		counter++;
	}

	if (counter >= MAX_ATTEMPTs) printf("No zeros where found within the first %d iterations with the required precision. The partial zero found is located at `%lf`.\n", counter, x);
	else printf("La funzione presenta uno zero in `%lf` con un errore di `%lf`.\n", x, e);

	return x;
}

double exeNewton(double (*f)(double), double (*f1)(double)){
	double x, e;

	printf("Type in the initial point and the error range: ");
	scanf("%lf %lf", &x, &e);

	return newton(x, e, f, f1);
}
