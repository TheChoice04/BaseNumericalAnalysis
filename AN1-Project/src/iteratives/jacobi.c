/*
 * jacobi.c
 *
 *  Created on: 23 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, "%lf %lf\n", x, fx)
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 MAX_ATTEMPTs
 */


#include "an1.iteratives.h"

int jacobi(Matrix A, Vector b, int n, Vector x, double err, int p);


/** jacobi ****************************************************************
 *
 *	This method evaluates the solution of a linear system updating the
 *	 solution `x^{(k)}` in:
 *	```math
 *	x^{(k+1)} = c - B * x^{(k)}
 *	```
 *	where
 *	```math
 *	c[i] = b[i]/A[i][i]
 *	```
 *	and
 *	```math
 *	C[i][j] =
 *	\begin{cases}
 *		B[i][j] / B[i][i]	&	\mbox{if } i \ne j\\
 *		0					&	\mbox{otherwise}
 *	\end{cases}
 *	```
 *
 *	The method continues until the error (evaluated in `p`-norm)
 *	 is smaller than `err`.
 *
 *	The method also print the sequence of normas found on a file called:
 *	 `results/iteratives/jacobi.txt`
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known term vector.
 *	@param n int: the dimension of the matrix and of the vector.
 *	@param x Vector: the unknown terms vector.
 *	@param err double: max error range.
 *	@param p int: norm counter.
 *
 *	@return int: exit-code:
 *	  `0` : success.
 *	  `1` : zero values on the matrix diagonal.
 *	  `2` : iteration number have overflow (no solution found).
 *
 *************************************************************************/

int jacobi(Matrix A, Vector b, int n, Vector x, double err, int p){
	int i, j, counter;  // counters
	Matrix Bj = NULL;   // updating matrix
	Vector cj = NULL;   // updating vector
	double norm;        // error norm
	FILE *fileP;        // output file pointer

	fileP = fopen("results/iteratives/jacobi.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/systems/jacobi.txt` in writing mode.\n");
		exit(1);
	}

	Bj = allocQMatrix(n);
	cj = allocVector(n);

	// Basis Construction
	for (i = 0; i < n; i++){
		if (A[i][i] == 0.0){
			free(Bj);
			free(cj);
			return 1;
		}
		for (j = 0; j < n; j++)
			if (i == j)
				Bj[i][j] = 0.0;
			else
				Bj[i][j] = - A[i][j]/A[i][i];
		cj[i] = b[i] / A[i][i];
	}

	counter = 0;
	norm = evalSystemError(A, x, b, n, n, p);
	while (norm > err && counter < MAX_ATTEMPTs){
		fprintPoint(fileP, (double) counter, norm);
		updateSolution(Bj, cj, x, n);
		norm = evalSystemError(A, x, b, n, n, p);
		counter++;
	}

	fprintPoint(fileP, (double) counter, norm);

	fclose(fileP);
	free(Bj);
	free(cj);

	if (counter >= MAX_ATTEMPTs){
		return 2;
	}

	printf("The solution was found in %d iterations.\n", counter--);

	return 0;
}
