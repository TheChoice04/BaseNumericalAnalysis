/*
 * directMenu.c
 *
 *  Created on: 16 nov 2018
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 */


#include "an1.direct.h"

int directMenu();


/** directMenu ************************************************************
 *
 * 	This function is meant to be a menu to choose between the Direct
 *   algorithms to solve the linear systems.
 *
 *	@return int exit-code:
 *	  `0` : Correct outcome
 *	  `2` : Wrong Function Choosing
 *	  `3` : Wrong Method Choosing
 *
 *************************************************************************/

int directMenu(){
	int c;              // choicer
	int m, n;           // dimensions
	int ret = 0;        // exit-code
	int ans;            // solver exit-code
	Matrix A = NULL;    // coefficient Matrix
	Matrix oA = NULL;   // original coefficient matrix
	Vector b = NULL;    // known terms Vector
	Vector ob = NULL;   // original known terms Vector
	Vector x = NULL;    // unknown vector

	parseLinearSystem(&A, &b, &m, &n);

	oA = copyMatrix(A, m, n);
	ob = copyVector(b, m);

	x = allocVector(n);

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Gaussian Elimination;\n");
	printf(" * type `2` to LU factorization;\n");
	printf(" * type `2` to Doolittle factorization;\n");
	printf(" * type `4` to Cholesky factorization;\n");
	printf(" * type `5` to QR factorization;\n");
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 5);
	ln;ln;


	switch (c) {
	case 1:
		printf("The original system is described by:\n");
		printSystem(A, b, m, n);
		ans = gaussianSolution(A, b, m, n, x);
		ln;
		if (ans == 2){
			printf("The system is under determined.\n");
		} else {
			printf("The application of Gaussian Elimination has given the following triangular system:\n");
			printSystem(A, b, m, n);
			if (ans == 0){
				printf("And the solution evaluated is:\n");
				printSolution(x, n);
			} else if (ans == 1){
				printf("The system is so not compatible.\n");
			}
			ln;
		}
		break;

	case 0:
		printf("Aborted\n");
		ans = -1;
		ret = 0;
		break;

	default:
		ans = -1;
		ret = 3;
		break;
	}

	if (ans == 0)
		printSystemError(oA, x, ob, m, n);

	free(A);
	free(b);
	free(oA);
	free(ob);
	free(x);

	return ret;
}





