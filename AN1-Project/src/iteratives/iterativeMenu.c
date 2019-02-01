/*
 * iterativeMenu.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 gnuplot(x) -> system("/usr/local/Cellar/gnuplot/5.2.5/bin/gnuplot "" -p 'gnuplot-scripts/"x"'")
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
 *	  `4` : Unespected ans return.
 *
 *************************************************************************/

int iterativeMenu(){
	int c;              // choicer
	int m, n;           // dimensions
	int p;              // norm value
	int ans;            // method exit-code
	int dd;             // diagonally dominance
	int pd;             // definiteness of the matrix
	int ret = 0;        // exit-code
	double err;         // error range
	double norm;        // the norm evaluated
	double omega;       // SOR parameter
	double beta;        // Richardson parameter
	Matrix A = NULL;    // coefficient Matrix
	Vector b = NULL;    // known terms Vector
	Vector x;           // unknown vector

	parseLinearSystem(&A, &b, &m, &n);

	if (n != m){
		printf("ERROR: Coefficient matrix must be a square matrix!.\n");
		printf("       You have instead parsed a %d by %d matrix.\n", m, n);
		printf("       Maybe you could try using Gaussian Method.\n");
		free(A);
		free(b);
		return 2;
	}

	dd = isDiagonallyDominant(A, n, n);
	//pd = isPositiveDefinite(A, n, n);
	pd = 0;

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

	printf("Type in an error range:\n");
	scanf("%lf", &err);

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Jacobi Method;\n");
	printf(" - type `2` to Gauss-Seidel method;\n");
	printf(" - type `3` to Successive Over Relaxation method;\n");
	printf(" * type `4` to Richardson method;\n");
	printf(" - type `0` to abort.\n");
	c = scanInt(0, 4);


	printf("The system is described by:\n");
	printSystem(A, b, m, n);

	switch (c) {
	case 1:
		if (dd == 0)
			printf("WARNING: the coefficient matrix is not Diagonally Dominant.\n");
		ans = jacobi(A, b, n, x, err, p);
		gnuplot("jacobi.gp");
		break;

	case 2:
		if (dd != 2 && pd != 1)
			printf("WARNING: the coefficient matrix is neither strictly Diagonally Dominant nor Defined Positive.\n");
		ans = gaussSeidel(A, b, n, x, err, p);
		gnuplot("gaussSeidel.gp");
		break;

	case 3:
		if (pd != 1)
			printf("WARNING: the coefficient matrix is not Positive Defined.\n");
		printf("Type in the relaxation parameter omega (range is `[0, 1]`).\n>> ");
		omega = scanDouble(0, 1);

		if (isApprox(omega, 1.0)){
			printf("Executing Gauss-Seidel method instead.\n");
			if (dd != 2 && pd != 1)
				printf("WARNING: the coefficient matrix is neither strictly Diagonally Dominant nor Defined Positive.\n");
			ans = gaussSeidel(A, b, n, x, err, p);
			gnuplot("gaussSeidel.gp");
			c = 2;
		} else {
			if (isApprox(omega, 0.0))
				printf("WARNING: the solution would not be incremented!\n");
			ans = successiveOverRelaxation(A, b, n, x, omega, err, p);
			gnuplot("successiveOverRelaxation.gp");
		}

		break;

	case 4:
		if (pd != 1)
			printf("WARNING: the coefficient matrix is not Positive Defined.\n");
		printf("Type in the Richardson multiply parameter beta (range is `[0, 1]`).\n");
		beta = scanDouble(0, 1);
		ans = richardson(A, b, n, x, beta, err, p);
		gnuplot("richardson.gp");
		break;

	case 0:
		printf("Aborted.\n");
		ans = -1;
		ret = 1;
		break;

	default:
		printf("WARNING: the method has not been encoded yet.\n");
		ans = -1;
		ret = 3;
	}

	norm = evalSystemError(A, x, b, n, n, p);

	if (ans == 0){
		printf("The application of the method has given the following solution:\n");
		printSolution(x, n);
		printf("Its error norm is %lf.\n\n", norm);
	} else if (ans == 1){
		printf("ERROR: The matrix must have non-zero value on its diagonal.\n");
	} else if (ans == 2){
		printf("No solutions were found within the first %d iterations with the required precision.\n", MAX_ATTEMPTs);
		printf("The partial solution found is:\n");
		printSolution(x, n);
		printf("Its error norm is %lf.\n\n", norm);
	} else if (ans != -1)
		ret = 4;

	free(A);
	free(b);
	free(x);

	return ret;
}
