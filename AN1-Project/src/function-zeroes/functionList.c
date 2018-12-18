//
//  functionList.c
//  ProjectManager
//
//  Created by Elia Onofri on 13/11/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#include "an1.function-zeroes.h"

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
