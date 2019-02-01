/*
 * successiveOverRelaxtion.c
 *
 *  Created on: 31 gen 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, "%lf %lf\n", x, fx)
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 MAX_ATTEMPTs
 */


#include "an1.iteratives.h"

int successiveOverRelaxation(Matrix A, Vector b, int n, Vector x, double omega, double err, int p);


/** successiveOverRelaxation **********************************************
 *
 *	This method evaluates the solution of a linear system updating the
 *	 solution `x^{(k)}` using a relaxation `omega` of Gauss-Seidel update:
 *	```math
 *	x^{(k+1)}[i] =
 *	   (1 - omega) * x^{(k)}[i] +
 *	   omega * (c[i] - B[i] * x^{(k)})
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
 *	Note that `omega`'s range is `[0, 1]` even if with:
 *	 - `omega = 0` there is no update of the solution.
 *	 - `omega = 1` the method is Gauss-Seidel's.
 *
 *	The method continues until the error (evaluated in `p`-norm)
 *	 is smaller than `err`.
 *
 *	The method also print the sequence of normas found on a file called:
 *	 `results/iteratives/SOR.txt`
 *
 *	@param A Matrix: the coefficient matrix.
 *	@param b Vector: the known term vector.
 *	@param n int: the dimension of the matrix and of the vector.
 *	@param x Vector: the unknown terms vector.
 *	@param omega double: the relaxation parameter.
 *	@param err double: max error range.
 *	@param p int: norm counter.
 *
 *	@return int: exit-code:
 *	  `0` : success.
 *	  `1` : zero values on the matrix diagonal.
 *	  `2` : iteration number have overflow (no solution found).
 *
 *************************************************************************/

int successiveOverRelaxation(Matrix A, Vector b, int n, Vector x, double omega, double err, int p){
	int i, j, counter;  // counters
	double k;           // iteration
	double temp;        // temp / accumulator
	Matrix Bgs = NULL;  // updating matrix
	Vector cgs = NULL;  // updating vector
	double norm;        // error norm
	FILE *fileP;        // output file pointer

	fileP = fopen("results/iteratives/SOR.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/systems/SOR.txt` in writing mode.\n");
		exit(1);
	}


	cgs = allocVector(n);
	Bgs = allocQMatrix(n);

	// Basis Construction
	for (i = 0; i < n; i++){
		if (A[i][i] == 0.0){
			free(cgs);
			free(Bgs);
			return 1;
		}
		temp = A[i][i];
		for (j = 0; j < n; j++)
			Bgs[i][j] = A[i][j] / temp;
		cgs[i] = b[i] / temp;
	}

	counter = 0;
	norm = evalSystemError(A, x, b, n, n, p);
	while (norm > err && counter < MAX_ATTEMPTs){
		k = counter / n;
		j = counter % n;
		fprintPoint(fileP, k, norm);

		// updating
		temp = cgs[j];
		for (i = 0; i < j; i++)
			temp = temp - Bgs[j][i] * x[i];
		for (i = j+1; i < n; i++)
			temp = temp - Bgs[j][i] * x[i];
		x[j] = (1 - omega) * x[j] + omega * temp;

		norm = evalSystemError(A, x, b, n, n, p);
		counter++;
	}

	fprintPoint(fileP, (double) counter, norm);

	fclose(fileP);
	free(Bgs);
	free(cgs);

	if (counter >= MAX_ATTEMPTs){
		return 2;
	}

	return 0;
}
