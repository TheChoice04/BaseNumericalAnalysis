//
//  functionList.c
//  ProjectManager
//
//  Created by Elia Onofri on 13/11/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#include "an1.iteratives.h"

/**
 * Everywhere in the code you can say
 *  double *f(double);
 *  f = &f1;
 * to set a fix value for f.
 */

double f1(double x){
    return exp(x)-1;
}

double df1(double x){
    return exp(x);
}

double f2(double x){
    return x/2-sin(x);
}

double df2(double x){
    return 1/2-cos(x);
}
