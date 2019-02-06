/*
 * gaussianElimination.c
 *
 *  Created on: 02 ott 2018
 *      Author: Elia Onofri
 *
 **
 *	Macros used:
 *	 allocate(num, type) -> ((type*)malloc(num * sizeof(type)))
 *	 Matrix -> double**
 *	 Vector -> double*
 */


#include "an1.direct.h"

int gaussianSolution(Matrix A, Vector b, int m, int n, Vector x);


/** gaussianSolution ******************************************************
 *
 *	This Function implements Gaussian Elimination over a double space
 *	 with both:
 *	  (0) no pivoting;
 *	  (1) partial pivoting;
 *	  (1) total pivoting.
 *
 *	Gaussian Elimination is a method to retrieve a Echelon matrix from
 *	 a given nxn matrix. This matrix could be loaded from a file or
 *	 from keyborad input:
 *	  - In order to read from a file it must be written as a .txt file
 *	    where the first element is the dimension `n` of the matrix,
 *	    followed by the n^2 elements of the matrix and by the n values of
 *	    the known terms.
 *	  - If you want to gain the values from keyboard you have to specify
 *	    the matrix dimension. Then you will be prompted in the insertion
 *	    of each and every single element. Tedious.
 *
 *	@param A Matrix: the coefficient matrix (will be modified).
 *	@param b Vector: the known terms vector (will be modified).
 *	@param m int: the number of rows (equations).
 *	@param n int: the number of columns (unknown).
 *	@param x Vector: the unknown vector (will be filled up);
 *
 *	@return int exit-code:
 *	  `0` : Success
 *	  `1` : Under-determined System.
 *	  `2` : Incompatible System.
 *
 *************************************************************************/

int gaussianSolution(Matrix A, Vector b, int m, int n, Vector x){
	int i, j, k;        // counters
	int max;            // max value (index) in the column
	int pivoting;       // kind of pivoting
	float aij;          // factor
	int *piv =          // pivoting vector (for total pivoting)
			allocate(n, int);

	if (m < n) {
		printf("ERROR: The system is under-determined.");
		return 1;
	}

	for (i = 0; i < n; i++)
		piv[i] = i;

	printf("===Running Gaussian Elimination===\n");
	printf("Do you want to have pivoting?\n");
	printf(" - type `0` for no pivoting;\n");
	printf(" - type `1` for partial pivoting;\n");
	printf(" * type `2` for total pivoting;\n");

	pivoting = scanInt(0, 2);

	// Row Cicle (only the first n rows)
	for (i = 0; i < n; i++){
		switch (pivoting) {
		// No Pivoting
		case 0:
			break;

			// Partial Pivoting
		case 1:
			max = i;
			for (j = i+1; j < m; j++)
				if (fabs(A[j][i]) > fabs(A[max][i]))
					max = j;

			if (max != i){
				double *app = A[i];
				A[i] = A[max];
				A[max] = app;
				double temp = b[i];
				b[i] = b[max];
				b[max] = temp;
			}
			break;



			// Total Pivoting
		case 2:
			//ToDo
			break;
		}
		// Check for singularity
		if (A[i][i] == 0.0){
			printMatrix(A, m, n);
			printf("ERROR: The coefficient matrix is Singular.\n");
			return 1;
		}
		// Row Cicle
		for (j = i+1; j < m; j++){
			// Head Coefficient Calculus
			aij = A[j][i]/A[i][i];
			// Column Cicle
			A[j][i] = 0.0;
			for (k = i+1; k < n; k++){
				A[j][k] = A[j][k] - (aij * A[i][k]);
			}
			b[j] = b[j] - (aij * b[i]);
		}


	}

	triSupSolver(A, b, m, n, x);

	return 0;
}


