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
	int dd;             // diagonally dominance
	double err;         // error range
	double norm;        // the norm evaluated
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

	dd = isDiagonallyDominant(A, n, n);

	printf("Do you want to choose a starting vector\n for the partial solution? (1 = Yes/0 = No)\n");
	c = scanInt(0, 1);
	if (c == 1)
		x = scanVector(n);
	else
		x = allocVector(n);

	printf("Choose a norm for the evaluation:\n");
	printf(" - type `1` for taxicab norm.\n");
	printf(" - type `2` for euclidean norm.\n");
	printf(" - type `0` for infinite norm.\n");
	p = scanInt(0, 2);

	printf("Type in an error range:\n>> ");
	scanf("%lf", &err);

	printf("You can choose one of the following:\n");
	printf(" * type `1` to Jacobi Method;\n");
	printf(" * type `2` to Gauss-Seidel method;\n");
	printf(" * type `2` to SOR method;\n");
	printf(" * type `4` to Richardson method;\n");
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 4);
	ln;ln;


	printf("The system is described by:\n");
	printSystem(A, b, m, n);

	switch (c) {
	case 1:
		if (dd == 0)
			printf("WARNING: the coefficient matrix is not Diagonally Dominant.\n");
		ans = jacobi(A, b, n, x, err, p);
		break;
/*
	case 2:
		ans = gaussSeidel(A, b, n, x, err, p);
		break;

	case 3:
		ans = sor(A, b, n, x, err, p);
		break;

	case 4:
		ans = richardson(A, b, n, x, err, p);
		break;
*/
	case 0:
		printf("Aborted\n");
		return 1;

	default:
		return 3;
	}

	norm = evalSystemError(A, x, b, n, n, p);

	if (ans == 0){
		printf("The application of the method has given the following solution:\n");
		printSolution(x, n);
		printf("Its error norm is %lf", norm);
	} else if (ans == 1){
		printf("ERROR: The matrix must have non-zero value on its diagonal.");
	} else if (ans == 2){
		printf("No solutions were found within the first %d iterations with the required precision.\n", MAX_ATTEMPTs);
		printf("The partial solution found is:\n");
		printSolution(x, n);
		printf("Its error norm is %lf.\n\n", norm);
	} else
		return 4;

	return 0;
}
