/*
 * directMenu.c
 *
 *  Created on: 16 nov 2018
 *      Author: Elia Onofri
 *
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 */


#include "an1.direct.h"

int directMenu();
void parseLinearSystem(Matrix* A, Vector* b, int * mp, int * np);


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
	int ans;            // exit-code
	Matrix A = NULL;    // coefficient Matrix
	Vector b = NULL;    // known terms Vector
	Vector x;           // unknown vector

	parseLinearSystem(&A, &b, &m, &n);

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
		printf("The application of Gaussian Elimination has given the following triangular system:\n");
		printSystem(A, b, m, n);
		printf("And the solution evaluated is:\n");
		printVector(n, x);
		ln;ln;
		break;

	case 0:
		printf("Aborted\n");
		return 0;

	default:
		return 3;
	}


	return 0;
}


/** parseLinearSystem *****************************************************
 *
 *	This method parse a linear system:
 *	  - from the default file;
 *	  - a particular file;
 *	  - with random values;
 *	  - from keyboard input.
 *
 *	The file must be built according to the following convention:
 *	  - the number of equations `m` (int);
 *	  - the number of unknowns `n` (int);
 *	  - a list of the coefficient for each rows + the known term (double).
 *	Everything after those numbers will be ignored so it could be used
 *	 as comments.
 *
 *	@param *Ap Matrix: The pointer to the coefficient matrix space
 *	                    (will be created).
 *	@param *bp Vector: The pointer to the known terms vector space
 *	                    (will be created).
 *	@param *mp int: pointer to the integer field of the equations number.
 *	@param *np int: pointer to the integer field of the unknowns number.
 *
 *	@return NULL
 *
 *************************************************************************/

void parseLinearSystem(Matrix* Ap, Vector* bp, int *mp, int *np){
	int    i, j;        // counters
	int    m, n;        // dimensions
	int    choice;      // choicer
	FILE   *fileP;      // file pointer
	double x;           // temp variable
	double min, max;    // random min and max
	Matrix A;           // coefficient matrix
	Vector b;           // known terms Vector

	printf("You can choose one of the following to parse a matrix:\n");
	printf(" - type `1` to parse the default system `source/GaussDefaultSystem.txt`;\n");
	printf(" - type `2` to parse a `.txt` file;\n");
	printf(" - type `3` to parse a random system;\n");
	printf(" - type `4` to parse a system manually (discouraged).\n");
	choice = scanInt(1, 4);
	ln;ln;

	if (choice == 1 || choice == 2){
		// Default Source
		if (choice == 1)
			fileP = fopen("source/GaussDefaultSystem.txt", "r");
		// Particular Source
		else{
			char filepath[256];
			printf("Please specify a file-path.\n>> ");
			fgets(filepath, 256, stdin);
			fileP = fopen(filepath, "r");
		}

		// Scann the Source
		fscanf(fileP, "%d %d", &m, &n);
		A = allocMatrix(m, n);
		b = allocVector(m);
		int np = n + 1;

		for (i=0; i<m*np; i++){
			fscanf(fileP, "%lf", &x);
			if (i%np == n)
				b[i/np] = x;
			else
				A[i/np][i%np] = x;
		}
		// Manual Scan
	} else {
		printf("Insert the number of equations:\n");
		m = scanInt(1, 100);
		ln;
		printf("Insert the number of unknowns:\n");
		ln;
		n = scanInt(1, 100);

		A = allocMatrix(m, n);
		b = allocVector(m);

		// Random Scan
		if (choice == 3){
			printf("Insert minimum and maximum values for your system value range:\n>> ");
			scanf("%lf %lf", &min, &max);
			ln;ln;
			for (i = 0; i < m; i++){
				for (j = 0; j < n; j++){
					A[i][j] = Random(min, max);
				}
				b[i] = Random(min, max);
			}
			// Manual Scan
		} else {
			for (i = 0; i < m; i++){
				printf("Insert the coefficient list for the %d-th equation and its known term:\n>> ", (i+1));
				for (j = 0; j < m; j++)
					scanf("%lf", &A[i][j]);
				scanf("%lf", &b[i]);
			}
		}
	}

	*Ap = A;
	*bp = b;
	*mp = m;
	*np = n;
	return ;
}
