//
//  gaussianElimination.c
//  AN410 Project Manager
//
//  Created by Elia Onofri on 02/10/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

/**
 *  This Function implements Gaussian Elimination with both no (0), partial (1)
 *    and total (2) pivoting over a double space.
 *  Gaussian Elimination is a method to retrieve a Echelon matrix from
 *    a given nxn matrix. This matrix could be loaded from a file or
 *    from keyborad input:
 *     - In order to read from a file it must be written as a .txt file
 *      where the first element is the dimension `n` of the matrix,
 *      followed by the n^2 elements of the matrix and by the n values of
 *      the known terms.
 *     - If you want to gain the values from keyboard you have to specify
 *      the matrix dimension. Then you will be prompted in the insertion of
 *      each and every single element. Tedious.
 *  @param A Matrix: the coefficient matrix associated to a linear system;
 *  @param b Vector: the known terms vector;
 *  @param m int: the number of rows (equations);
 *  @param n int: the number of columns (unknown).
 *
 *  @return int exit-code integer:
 *      `0` : Success;
 *      `1` : Under-determined System.
 *      `2` : Incompatible System.
 */

#include "an1.direct.h"

int gaussianSolution(Matrix A, Vector b, int m, int n){
	int i, j, k, max, pivoting;
	Matrix M;
	float mij;

	if (m < n) {
		printf("ERROR: The system is under-determined.");
		return 1;
	}

	M = allocMatrix(m, n+1);
	for (i = 0; i < m; i++){
		for (k = 0; k < n; k++){
			M[i][k] = A[i][k];
		}
		M[i][n] = b[i];
	}

	printf("===Running Gaussian Solution===");
	printf("Do you want to have pivoting?\n");
	printf(" - type `0` for no pivoting;\n");
	printf(" - type `1` for partial pivoting;\n");
	printf(" * type `2` for total pivoting;\n>> ");

	scanf("%d", &pivoting);

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
				if (fabs(M[j][i]) > fabs(M[max][i]))
					max = j;

			if (max != i){
				double *app;
				app = M[i];
				M[i] = M[max];
				M[max] = app;
			}
			break;

			// Total Pivoting
		case 2:
			//ToDo
			break;
		}
		// Check for singularity
		if (M[i][i] == 0.0){
			printf("ERROR: The coefficient matrix is Singular.");
			return 1;
		}
		// Row Cicle
		for (j=i+1; j<n; j++){
			// Head Coefficient Calculus
			mij = M[j][i]/M[i][i];
			// Column Cicle
			for (k=i; k<n; k++){
				M[j][k] = M[j][k] - (mij*M[i][k]);
			}
		}


	}

	return 0;
}


