/*
 * richardson.c
 *
 *  Created on: 1 feb 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, "%lf %lf\n", x, fx)
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 MAX_ATTEMPTs
 */


#include "an1.iteratives.h"

int richardson(Matrix A, Vector b, int n, Vector x, double beta, double err, int p);


/** richardson ************************************************************
 *
 *	This method evaluates the solution of a linear system updating the
 *	 solution `x^{(k)}` by adding to it a multiply of the remainder vector
 *	 `Ax^{(k)} - b`, in formulas:
 *	```math
 *	x^{(k+1)} = x^{(k)} - \beta(A * x^{(k)} - b), \qquad\beta\in\mathbb R
 *	```
 *	in other worlds making the following upgrade:
 *	```math
 *	x^{(k+1)} = B_R * x^{(k)} + c_R
 *	```
 *	where
 *	```math
 *	B_r = I - \beta * A \qquad c_R = \beta * b
 *	```
 *
 *	The method continues until the error (evaluated in `p`-norm)
 *	 is smaller than `err`.
 *
 *	The method also print the sequence of normas found on a file called:
 *	 `results/iteratives/richardson.txt`
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known term vector.
 *	@param n int: the dimension of the matrix and of the vector.
 *	@param x Vector: the unknown terms vector.
 *	@param beta double: the Richardson constant.
 *	@param err double: max error range.
 *	@param p int: norm counter.
 *
 *	@return int: exit-code:
 *	  `0` : success.
 *	  `2` : iteration number have overflow (no solution found).
 *
 *************************************************************************/

int richardson(Matrix A, Vector b, int n, Vector x, double beta, double err, int p){
	int i, j, counter;  // counters
	Matrix Br = NULL;   // updating matrix
	Vector cr = NULL;   // updating vector
	double norm;        // error norm
	FILE *fileP;        // output file pointer

	fileP = fopen("results/iteratives/richardson.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/systems/richardson.txt` in writing mode.\n");
		exit(1);
	}


	cr = allocVector(n);
	Br = allocQMatrix(n);

	// Basis Construction
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			if(i == j)
				Br[i][i] = 1.0 - beta * A[i][i];
			else
				Br[i][j] = - beta * A[i][j];
		cr[i] = beta * b[i];
	}

	counter = 0;
	norm = evalSystemError(A, x, b, n, n, p);
	while (norm > err && counter < MAX_ATTEMPTs){
		fprintPoint(fileP, (double) counter, norm);

		// updating
		updateSolution(Br, cr, x, n);

		norm = evalSystemError(A, x, b, n, n, p);
		counter++;
	}

	fprintPoint(fileP, (double) counter, norm);

	fclose(fileP);
	free(Br);
	free(cr);

	if (counter >= MAX_ATTEMPTs){
		return 2;
	}

	printf("The solution was found in %d iterations.\n", counter--);

	return 0;
}
