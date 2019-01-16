/*
 * lagrange.c
 *
 *  Created on: 18 dic 2018
 *      Author: Elia
 */


#include "an1.interpolation.h"

int lagrange(double (*f)(double), int npts, Vector knot, int dpts, float a, float b){
	float step = (b-a)/(dpts-1);
	float x = a, acc, L, err;
	int i, j, k;
	int n = npts-1;
	Vector knotVal = allocVector(npts);
	FILE *file = fopen("interpolation.lagrange.txt", "w");

	if (file == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}

	if (dpts <= 0) {
		printf("ERROR: no data points selected.\n");
		exit(1);
	}

	for (i = 0; i <= n; i++){
		knotVal[i] = f(knot[i]);
	}

	for (k = 0; k <= dpts; k++){
		acc = 0;
		for (i = 0; i <= n; i++){
			L = 1;
			for (j = 0; j <= n; j++){
				if (i != j) {
					L = L * (x - knot[j])/(knot[i] - knot[j]);
				}
			}
			acc += (L * knotVal[i]);
		}
		err = fabs(f(x)-acc);
		fprintf(file, "%lf %lf %lf", x, acc, err);
		x += step;
	}

	fclose(file);

	return 0;
}
