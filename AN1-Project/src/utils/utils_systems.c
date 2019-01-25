/*
 * utils_systems.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 *	 isApproxZero(x) -> fabs(x) < ERR
 *	 ln -> printf("\n")
 *	 Vector -> double*
 *	 Matrix -> double**
 */


#include "an1.utils.h"

void parseLinearSystem(Matrix* Ap, Vector* bp, int *mp, int *np);
void printSystem(Matrix, Vector, int, int);
void printSolution(Vector x, int n);
double evalSystemError(Matrix A, Vector x, Vector b, int m, int n, int p);
void evalSystemError(Matrix A, Vector x, Vector b, int m, int n);

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
	printf(" - type `1` to parse the default system `source/DefaultSystem.txt`;\n");
	printf(" - type `2` to parse a `.txt` file;\n");
	printf(" - type `3` to parse a random system;\n");
	printf(" - type `4` to parse a system manually (discouraged).\n");
	choice = scanInt(1, 4);
	ln;ln;

	if (choice == 1 || choice == 2){
		// Default Source
		if (choice == 1)
			fileP = fopen("source/DefaultSystem.txt", "r");
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


/** printSystem ***********************************************************
 *
 *	This method prints the system described by the coefficient matrix `A`
 *	 and the known terms `b` in the unknown `x_0 ... x_{n-1}`.
 *
 *	@param A Matrix: The coefficient matrix.
 *	@param b Vector: The known terms vector.
 *	@param m int: The number of equations (row) the system is made of.
 *	               Must be equal to the number of known terms in `b`.
 *	@param n int: The number of unknowns (column) the system is made of.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printSystem(Matrix A, Vector b, int m, int n){
	int i, j;           // counters
	for (i = 0; i < m; i++){
		printf("  | ");
		for (j = 0; j < n; j++){
			if ( !(isApproxZero(A[i][j])) ){
			printf("%lf x_%d", A[i][j], j);
			if (j < n-1)
				printf(" + ");
			}
		}
		printf(" = %lf\n", b[i]);
	}
	printf("\n");
}


/** printSolution *********************************************************
 *
 *	This method prints the unknown vector `x_0 ... x_{n-1}`.
 *
 *	@param x Vector: The unknown terms vector.
 *	@param n int: The number of unknowns.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printSolution(Vector x, int n){
	int i;              // counter
	for (i = 0; i < n; i++)
		printf("  x_%d = %lf\n", i, x[i]);
	printf("\n");
}


//
//	Errors
//

/** evalSystemError *******************************************************
 *
 *	This method evaluate the approximation error made during the calculus
 *	 of a system in the form `Ax = b` by performing the norm of `Ax - b`.
 *
 *	@param A Matrix: The coefficient matrix.
 *	@param x Vector: The solution that needs to be evaluated.
 *	@param b Vector: The known terms vector.
 *	@param m int: The number of equations (row) the system is made of.
 *	@param n int: The number of unknowns (column) the system is made of.
 *	@param p int: Norm value.
 *
 *	@return double: the norm evaluated.
 *
 *************************************************************************/

double evalSystemError(Matrix A, Vector x, Vector b, int m, int n, int p){
	int i;              // counter
	double norm;        // error norm
	Vector b1;          // effective result of `Ax`
	Vector err;         // error vector

	b1 = allocVector(m);
	err = allocVector(m);

	multMV(A, x, m, n, b1);

	for (i = 0; i < m; i++){
		err[i] = fabs(b1[i] - b[i]);
	}

	norm = pNorm(err, m, p);

	return norm;
}

/** printSystemError *******************************************************
 *
 *	This method evaluate the approximation error made during the calculus
 *	 of a system in the form `Ax = b` by performing the norm of `Ax - b`.
 *	Then it is displayed in the three normas:
 *	 - Taxicab norm.
 *	 - Euclidean norm.
 *	 - Infinity norm.
 *
 *	@param A Matrix: The coefficient matrix.
 *	@param x Vector: The solution that needs to be evaluated.
 *	@param b Vector: The known terms vector.
 *	@param m int: The number of equations (row) the system is made of.
 *	@param n int: The number of unknowns (column) the system is made of.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printSystemError(Matrix A, Vector x, Vector b, int m, int n){
	int i;              // counter
	double norm;        // error norm
	Vector b1;          // effective result of `Ax`
	Vector err;         // error vector

	b1 = allocVector(m);
	err = allocVector(m);

	multMV(A, x, m, n, b1);

	for (i = 0; i < m; i++){
		err[i] = fabs(b1[i] - b[i]);
	}

	printf("The error norm is:\n");
	norm = taxicabNorm(err, m);
	printf(" - Taxicaban norm : %lf.\n", norm);

	norm = euclideanNorm(err, m);
	printf(" - Euclidean norm : %lf.\n", norm);

	norm = infinityNorm(err, m);
	printf(" - infinity norm : %lf.\n", norm);


}
