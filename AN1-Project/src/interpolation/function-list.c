/*
 * function-list.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */


#include "an1.interpolation.h"

/**
 * Everywhere in the code you can say
 *  double *f(double);
 *  f = &f1;
 * to set a fix value for f.
 */

double samplef1(double x){
	return exp(x)-1;
}

double dsamplef1(double x){
	return exp(x);
}

double samplef2(double x){
	return x/2-sin(x);
}

double dsamplef2(double x){
	return 1/2-cos(x);
}
