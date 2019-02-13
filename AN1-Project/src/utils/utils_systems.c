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

int parseLinearSystem(Matrix* Ap, Vector* bp, int *mp, int *np);
void updateSolution(Matrix B, Vector c, Vector x, int n);
void printSystem(Matrix, Vector, int, int);
void printSolution(Vector x, int n);
double evalSystemError(Matrix A, Vector x, Vector b, int m, int n, int p);
void printSystemError(Matrix A, Vector x, Vector b, int m, int n);

/** parseLinearSystem *****************************************************
 *
 *	This method parse a linear system:
 *	  - from the default file;
 *	  - from a particular file;
 *	  - a Vandermonde matrix coefficient matrix;
 *	  - an Hilbert coefficient matrix;
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
 *	@return int exit-code:
 *	  `0` : Correct outcome.
 *	  `3` : Method not encoded yet.
 *
 *************************************************************************/

int parseLinearSystem(Matrix* Ap, Vector* bp, int *mp, int *np){
	int i, j;           // counters
	int m, n;           // dimensions
	int n1;             // n plus 1
	int choice;         // choicer
	FILE *fileP;        // file pointer
	char filepath[256]; // file path to .txt
	double x;           // temp variable
	double min, max;    // random min and max
	Matrix A = NULL;    // coefficient matrix
	Vector b = NULL;    // known terms Vector

	printf("You can choose one of the following to parse a matrix:\n");
	printf(" - type `1` to parse the default system `source/DefaultSystem.txt`;\n");
	printf(" * type `2` to parse a `.txt` file;\n");
	printf(" - type `3` to parse a Vandermonde system;\n");
	printf(" - type `4` to parse a Hilbert system;\n");
	printf(" - type `5` to parse a random system;\n");
	printf(" - type `6` to parse a system manually (discouraged).\n");
	choice = scanInt(1, 6);

	switch (choice) {
	case 1 :
		fileP = fopen("source/DefaultSystem.txt", "r");
		if (fileP == NULL){
			printf("ERROR: can't open the source file in reading mode.\n");
			exit(1);
		}

		// Scan the Source
		fscanf(fileP, "%d %d", &m, &n);

		break;

	case 2:
		printf("Please specify a file-path.\n>> ");
		fgets(filepath, 256, stdin);
		fileP = fopen(filepath, "r");
		if (fileP == NULL){
			printf("ERROR: can't open the source file in reading mode.\n");
			exit(1);
		}

		// Scan the Source
		fscanf(fileP, "%d %d", &m, &n);
		break;

	case 3:
	case 4:
	case 5:
	case 6:
		printf("Type in the number of equations:\n");
		m = scanInt(1, 100);
		printf("Type in the number of unknowns:\n");
		n = scanInt(1, 100);
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;
	}

	A = allocMatrix(m, n);
	b = allocVector(m);

	switch (choice){
	case 1:
	case 2:
		n1 = n + 1;

		for (i = 0; i < m * n1; i++){
			fscanf(fileP, "%lf", &x);
			if (i%n1 == n)
				b[i/n1] = x;
			else
				A[i/n1][i%n1] = x;
		}

		fclose(fileP);
		break;

	case 3: // Vandermonde
		for (i = 0; i < m; i ++){
			A[i][0] = 1.0;
			printf("Type in the %d-th Vandermonde coefficient and the corresponding known term:\n>> ", i+1);
			scanf("%lf %lf", &x, &b[i]);
			for(j = 1; j < n; j++){
				A[i][j] = A[i][j-1] * x;
			}
		}
		break;

	case 4:	// Hilbert
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				A[i][j] = 1.0/(i + j + 1);
		printf("Type in the %d known terms:\n>> ", m);
		for (i = 0; i < m; i++)
			scanf("%lf", &b[i]);

		break;
	case 5:	// Random
		printf("Type in minimum and maximum values for your system value range:\n>> ");
		scanf("%lf %lf", &min, &max);
		ln;
		for (i = 0; i < m; i++){
			for (j = 0; j < n; j++){
				A[i][j] = Random(min, max);
			}
			b[i] = Random(min, max);
		}
		break;

	case 6:	// Manual
		for (i = 0; i < m; i++){
			printf("Type in the coefficient list for the %d-th equation and its known term:\n>> ", (i+1));
			for (j = 0; j < m; j++)
				scanf("%lf", &A[i][j]);
			scanf("%lf", &b[i]);
		}
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;

	}



	*Ap = A;
	*bp = b;
	*mp = m;
	*np = n;
	return 0;
}


/** updateSolution ********************************************************
 *
 *	This method updates a vector `x` with a matrix multiplication by `B`
 *	 and a vector sum by `c`. In other worlds it is evaluating the assign:
 *	```C
 *	x = (x * B) + c;
 *	```
 *
 *	@param B Matrix: updating Matrix.
 *	@param c Vector: updating Vector.
 *	@param x Vector: vector to be updated (will be filled).
 *	@param n int: dimension of the vector.
 *
 *	@return NULL.
 *
 *************************************************************************/

void updateSolution(Matrix B, Vector c, Vector x, int n){
	Vector x0 = NULL;   // copy of the original vector `x`

	x0 = copyVector(x, n);

	multMV(B, x0, n, n, x);

	sumVV(x, c, n, x);

	free(x0);
}


/** printSystem ***********************************************************
 *
 *	This method prints the system described by the coefficient matrix `A`
 *	 and the known terms `b` in the unknown `x_0 ... x_{n-1}`.
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known terms vector.
 *	@param m int: the number of equations (row) the system is made of.
 *	               Must be equal to the number of known terms in `b`.
 *	@param n int: the number of unknowns (column) the system is made of.
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
				printf(""lfpf" x_%d ", A[i][j], j);
			}
		}
		printf("= "lfpf"\n", b[i]);
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
		printf("  x_%d = "lfpf"\n", i, x[i]);
	return ;
}


//
//	Errors
//

/** evalSystemError *******************************************************
 *
 *	This method evaluate the approximation error made during the calculus
 *	 of a system in the form `Ax = b` by performing the norm of `Ax - b`.
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param x Vector: the solution that needs to be evaluated.
 *	@param b Vector: the known terms vector.
 *	@param m int: the number of equations (row) the system is made of.
 *	@param n int: the number of unknowns (column) the system is made of.
 *	@param p int: norm value.
 *
 *	@return double: the norm evaluated.
 *
 *************************************************************************/

double evalSystemError(Matrix A, Vector x, Vector b, int m, int n, int p){
	int i;              // counter
	double norm;        // error norm
	Vector b1 = NULL;   // effective result of `Ax`
	Vector err = NULL;  // error vector

	b1 = allocVector(m);
	err = allocVector(m);

	multMV(A, x, m, n, b1);

	for (i = 0; i < m; i++){
		err[i] = fabs(b1[i] - b[i]);
	}

	norm = pNorm(err, m, p);

	free(b1);
	free(err);

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
 *	@param A Matrix: the coefficient matrix.
 *	@param x Vector: the solution that needs to be evaluated.
 *	@param b Vector: the known terms vector.
 *	@param m int: the number of equations (row) the system is made of.
 *	@param n int: the number of unknowns (column) the system is made of.
 *
 *	@return NULL.
 *
 *************************************************************************/

void printSystemError(Matrix A, Vector x, Vector b, int m, int n){
	int i;              // counter
	double norm;        // error norm
	Vector b1 = NULL;   // effective result of `Ax`
	Vector err = NULL;  // error vector

	b1 = allocVector(m);
	err = allocVector(m);

	multMV(A, x, m, n, b1);

	for (i = 0; i < m; i++){
		err[i] = fabs(b1[i] - b[i]);
	}

	printf("The error norm is:\n");
	norm = taxicabNorm(err, m);
	printf(" - Taxicaban norm : %10e.\n", norm);

	norm = euclideanNorm(err, m);
	printf(" - Euclidean norm : %10e.\n", norm);

	norm = infinityNorm(err, m);
	printf(" - infinity norm : %10e.\n", norm);

	free(b1);
	free(err);


}
