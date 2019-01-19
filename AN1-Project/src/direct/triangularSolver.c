/*
 * triangularSolver.c
 *
 *  Created on: 19 gen 2019
 *      Author: Elia
 */


#include "an1.direct.h"

int triSupSolver(Matrix A, Vector b, int m, int n);
int triInfSolver(Matrix A, Vector b, int m, int n);

/**
 * This method solve a triangular system in input.
 *
 * @return int: `0` compatible;
 * 				`1` not compatible.
 */
int triSupSolver(Matrix A, Vector b, int m, int n){
	int i, j;
	double *x = allocate(n, double);

	// if m > n
	for (i = n; i < m; i++){
		if (b[i] <= ERR){
			printf("The system is not compatible.\n\n");
			return 1;
		}

	}
	printf("%lf", b[0]);

	for (i = n-1; i >= 0; i--){
		double acc = b[i];
		for (j = i+1; i < n; i++)
			acc = acc - (A[i][j] * x[j]);
		x[i] = acc / A[i][i];
	}
	printVector(n, x);

	return 0;
}

int triInfSolver(Matrix A, Vector b, int m, int n){

}
