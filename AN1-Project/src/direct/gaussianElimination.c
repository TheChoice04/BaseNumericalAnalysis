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
 *  @param A Matrix: the complete matrix associated to a linear system;
 *  @param n int: the number of columns (unknown + 1).
 *  @param m int: the number of rows (equations).
 *
 *  @return int exit-code integer:
 *      `0` : Success;
 *      `1` : undefined error.
 */

#include "an1.direct.h"

Matrix parseSource(int *);

int gaussianSolution(Matrix A, int n, int m){
	const int pivoting = 1;
	int i, j, k, max;

	for (i = 0; i < m; i++){
		switch (pivoting) {
		case 0:
			break;

		case 1:
			max = i;
			for (j = i+1; j < m; j++)
				if (fabs(A[j][i]) > fabs(A[max][i]))
					max = j;
			if (max != i){
				double *app;
				app = A[i];
				A[i] = A[max];
				A[max] = app;
			}
			break;
		case 2:
			//To Do
			break;
		}



	}

	return 0;
}

int gaussianElimination(){
    const int pivoting = 1;
    int i, j, k, n;
    int *np = malloc(sizeof(int));
    double mij;
    double **A;
    
    printf("\n");
    printf("================================\n");
    printf("======Gaussian Elimination======\n");
    printf("================================\n");
    printf("\n");
    A = parseSource(np);
    n = *np;


    // Column Cicle
    for (i=0; i<n; i++){
    	// Pivoting
    	if (pivoting == 1){
    		int max = i+1;
    		for (j=i+2; j<n; j++){
    			if (fabs(A[j][i]) > fabs(A[max][i])){
    				max = j;
    			}
    		}
    		if (max != i+1){
    			double *app;
    			app = A[i+1];
    			A[i+1] = A[max];
    			A[max] = app;

    			//ln;
    			//printQMatrix(n, A);
    		}
    	}
    	// Row Cicle
    	for (j=i+1; j<n; j++){
    		// Head Coefficient Calculus
    		mij = A[j][i]/A[i][i];
    		// Row Cicle
    		for (k=i; k<n; k++){
    			A[j][k] = A[j][k] - (mij*A[i][k]);
    		}
    	}
    }
    ln;
    ln;
    printf("Associated Echelon Matrix is:\n");
    printQMatrix(n, A);
    
    return -1;
}

Matrix parseSource(int *np){
    int i, n=0;
    double x;
    int choice;
    double **mat;
    FILE *fileP;
    
    printf("Do you want to parse Default File:\n");
    printf("\t`source/GaussElimMatrix.txt`? (1=yes/0=no)");
    scanf("%d", &choice);
    
    if (choice == 1) {
        fileP = fopen("source/GaussElimMatrix.txt", "r");
        fscanf(fileP, "%d", &n);
        mat = allocQMatrix(n);
        
        for (i=0; i<n*n; i++){
            fscanf(fileP, "%lf", &x);
            mat[i/n][i%n] = x;
        }
    } else {
    	printf("Insert the Matrix Dimension: ");
    	scanf("%d", &n);

        mat = parseQMatrix(n);
    }
    
    np[0] = n;                                                                  ////??
    
    printf("\n======Data Reading Complete======\n\n");
    
    printf("n = %d\n", *np);
    printf("Matrix A has been parsed in:\n");
    printQMatrix(*np, mat);
    return mat;
}


