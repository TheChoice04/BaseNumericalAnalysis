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
	Vector soluz = allocVector(n);
	double acc;
	for (i = 0; i < n; i++){
		soluz[i] = 0.0;
	}

	// if m > n
	for (i = n; i < m; i++){
		if (b[i] >= ERR){
			printf("The system is not compatible.\n\n");
			return 1;
		}

	}

	for (i = n-1; i >= 0; i--){
		acc = b[i];
		for (j = i+1; j < n; j++)
			acc = acc - (A[i][j] * soluz[j]);
		acc = acc / A[i][i];
		soluz[i] = acc;
	}
	printVector(n, soluz);

	return 0;
}

int triInfSolver(Matrix A, Vector b, int m, int n){
	return 0;
}
