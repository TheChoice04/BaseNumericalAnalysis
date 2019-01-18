/*
 * directMenu.c
 *
 *  Created on: 16 nov 2018
 *      Author: Elia
 */

#include "an1.direct.h"


/**
 * This function is meant to be a menu to choose between the Direct
 *  algorithms to solve the linear systems.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 */

int directMenu(){
	int c, m, n;
	int ans;
	Matrix A;
	Vector b;

	int dim[2];
	dim = parseLinearSystem(A, b);
	m = dim[0];
	n = dim[1];

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Gaussian Elimination;\n");
	printf(" * type `2` to LU factorization;\n");
	printf(" * type `3` to LU factorization;\n");
	printf(" * type `4` to QR factorization;\n");
	printf(" - type `0` to quit.\n\n");

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");


	switch (c) {
	case 1:
		ans = gaussianSolution(A, b, m, n);
		int i;
		for (i = 0; i < m; i++)
			printf("%lf", b[i]);
		break;

	case 0:
		printf("Aborted\n");
		break;

	default:
		return 3;
	}

	return 0;
}

int parseSource(Matrix A, Vector b){
	int i, j, m, n, ret[2];

	return ret;
}
/*
	int i, n=0;
	double x;
	int choice;
	double **mat;
	FILE *fileP;

	printf("Do you want to parse Default File:\n");
	printf("\t`source/GaussElimMatrix.txt`? (1=yes/0=no)");
	scanf("%d", &choice);

	if (choice == 1) {
		fileP = fopen("source/GaussElimMatrix.txt", "r");
		fscanf(fileP, "%d", &n);
		mat = allocQMatrix(n);

		for (i=0; i<n*n; i++){
			fscanf(fileP, "%lf", &x);
			mat[i/n][i%n] = x;
		}
	} else {
		printf("Insert the Matrix Dimension: ");
		scanf("%d", &n);

		mat = parseQMatrix(n);
	}

	np[0] = n;                                                                  ////??

	printf("\n======Data Reading Complete======\n\n");

	printf("n = %d\n", *np);
	printf("Matrix A has been parsed in:\n");
	printQMatrix(*np, mat);
	return mat;
*/
