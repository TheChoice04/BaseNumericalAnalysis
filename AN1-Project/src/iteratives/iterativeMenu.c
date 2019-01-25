/*
 * iterativeMenu.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 Matrix -> double**
 *	 Vector -> double*
 */


#include "an1.iteratives.h"

int iterativeMenu();


/** iterativeMenu *********************************************************
 *
 *	This function is meant to be a menu to choose between the Direct
 *   algorithms to solve the linear systems.
 *
 *	@return int exit-code:
 *	  `0` : Correct outcome.
 *	  `1` : Aborted.
 *	  `2` : Parsed matrix is not square.
 *	  `3` : Wrong Method Choosing.
 *
 *************************************************************************/

int iterativeMenu(){
	int c;              // choicer
	int m, n;           // dimensions
	int p;              // norm value
	int ans;            // method exit-code
	double err;         // error range
	Matrix A = NULL;    // coefficient Matrix
	Vector b = NULL;    // known terms Vector
	Vector x;           // unknown vector

	parseLinearSystem(&A, &b, &m, &n);

	if (n != m){
		printf("ERROR: Coefficient matrix must be a square matrix!.\n");
		printf("       You have instead parsed a %d by %d matrix.\n", m, n);
		printf("       Maybe you could try using Gaussian Method.\n");
		return 2;
	}

	x = allocVector(n);

	printf("Choose a norm for the evaluation:\n");
	printf(" - type `1` for taxicab norm.\n");
	printf(" - type `2` for euclidean norm.\n");
	printf(" - type `0` for infinite norm.\n");
	p = scanInt(0, 2);

	printf("Type in an error range:\n>> ");
	scanf("%lf", err);

	printf("You can choose one of the following:\n");
	printf(" * type `1` to Jacobi Method;\n");
	printf(" * type `2` to Gauss-Seidel method;\n");
	printf(" * type `2` to SOR method;\n");
	printf(" * type `4` to Richardson method;\n");
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 4);
	ln;ln;


	switch (c) {
	case 1:
		printf("The original system is described by:\n");
		printSystem(A, b, m, n);
		ans = jacobi(A, b, n, x, err, p);
		printf("The application of Jacobi method has given the following solution:\n");
		printVector(x, n);
		break;

	case 0:
		printf("Aborted\n");
		return 1;

	default:
		return 3;
	}

	if (ans == 0)
	evalSystemError(A, x, b, m, n);

	return 0;
}
