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
 *	  `1` : Incompatible System.
 *	  `2` : Under-determined System.
 *
 *************************************************************************/

int gaussianSolution(Matrix A, Vector b, int m, int n, Vector x){
	int i, j, k;        // counters
	int p, q;           // printer counters
	int ans;            // compatibility
	int maxR;           // max value (index) of the row
	int maxC;           // max value (index) of the column
	int pivoting;       // kind of pivoting
	float aij;          // factor
	int *piv            // total pivoting index vector
	= calloc(n, sizeof(int));
	Vector xp = NULL;   // total pivoted solution vector x
	Matrix Ap = NULL;   // total pivoted matrix A
	FILE *fileP;        // output file pointer

	if (m < n) {
		printf("ERROR: The system is under-determined.");
		free(piv);
		return 2;
	}

	fileP = fopen("results/direct/gaussian_elimination.txt", "w");

	if (fileP == NULL) {
		printf("ERROR: can't open `results/direct/gaussian_elimination.txt` in writing mode.\n");
		free(piv);
		exit(1);
	}

	for (p = 0; p < m; p++){
		for (q = 0; q < n; q++)
			fprintf(fileP, ""flfpf"  ", A[p][q]);
		fprintf(fileP, "|  "flfpf"\n", b[p]);
	}
	fprintf(fileP, "\n\n");

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
			maxR = i;
			for (j = i+1; j < m; j++)
				if (fabs(A[j][i]) > fabs(A[maxR][i]))
					maxR = j;

			if (maxR != i){
				double *app = A[i];
				A[i] = A[maxR];
				A[maxR] = app;
				double temp = b[i];
				b[i] = b[maxR];
				b[maxR] = temp;
			}
			break;

			// Total Pivoting
		case 2:
			maxR = i;
			maxC = i;

			for (j = i; j < m; j++){
				for (k = i; k < n; k++){
					if (fabs(A[j][k]) > fabs(A[maxR][piv[maxC]])){
						maxR = j;
						maxC = k;
					}
				}
			}
			// Row inversion
			if (maxR != i){
				double *app = A[i];
				A[i] = A[maxR];
				A[maxR] = app;
				double temp = b[i];
				b[i] = b[maxR];
				b[maxR] = temp;
			}
			// Column inversion
			if (maxC != i){
				int p = piv[i];
				piv[i] = piv[maxC];
				piv[maxC] = p;
			}

			break;
		}
		// Check for singularity
		if (A[i][piv[i]] == 0.0){
			printMatrix(A, m, n);
			printf("ERROR: The coefficient matrix is Singular.\n");
			return 1;
		}
		// Row Cicle
		for (j = i+1; j < m; j++){
			// Head Coefficient Calculus
			aij = A[j][piv[i]]/A[i][piv[i]];
			// Column Cicle
			A[j][piv[i]] = 0.0;
			for (k = i+1; k < n; k++){
				A[j][piv[k]] = A[j][piv[k]] - (aij * A[i][piv[k]]);
			}
			b[j] = b[j] - (aij * b[i]);
		}

		fprintf(fileP, "Cicle no.%d\nPivotation vector:\t[", i+1);
		for (q = 0; q < n; q++)
			fprintf(fileP, "%d ", piv[q]);
		fprintf(fileP, "]\n");

		for (p = 0; p < m; p++){
			for (q = 0; q < n; q++)
				fprintf(fileP, ""flfpf"  ", A[p][q]);
			fprintf(fileP, "|  "flfpf"\n", b[p]);
		}
		fprintf(fileP, "\n\n");


	}

	Ap = allocMatrix(m, n);
	xp = allocVector(n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			Ap[i][j] = A[i][piv[j]];

	fprintf(fileP, "Pivoted Matrix:\n");

	for (p = 0; p < m; p++){
		for (q = 0; q < n; q++)
			fprintf(fileP, ""flfpf"  ", Ap[p][q]);
		fprintf(fileP, "|  "flfpf"\n", b[p]);
	}
	fprintf(fileP, "\n\n");

	ans = triSupSolver(Ap, b, m, n, xp);

	for (i = 0; i < n; i++)
		x[i] = xp[piv[i]];

	if (ans == 0){
		for (i = 0; i < n; i++)
			fprintf(fileP, "x[%d] = "flfpf"\n", i, x[i]);
	} else if (ans == 1) {
		fprintf(fileP, "The system is not compatible.");
	} else {
		fprintf(fileP, "ERROR: Something unexpected happened.");
	}

	fclose(fileP);
	free(piv);

	return ans;
}


