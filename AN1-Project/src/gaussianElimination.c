//
//  gaussianElimination.c
//  AN410 Project Manager
//
//  Created by Elia Onofri on 02/10/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

/**
 *  This Function implements Gaussian Elimination with both partial (1)
 *    and total (2) pivoting over a double space.
 *  Gaussian Elimination is a method to retrieve a echelon matrix from
 *    a given nxn matrix. This matrix could be loaded from a file or
 *    from keyborad input:
 *     - In order to read from a file it must be written as a .txt file
 *      where the first element is the dimension `n` of the matrix,
 *      followed by the n^2 elements of the matrix.
 *     - If you want to gain the values from keyboard you have to specify
 *      the matrix dimension. Then you will be prompted in the insertion of
 *      each and every single element. Tedious.
 *  @return int exit-code integer:
 *      `0` : Success;
 *      `1` : undefined error.
 */

#include "mainHeader.h"

Matrix parseSource(int *);

int gaussianElimination(){
    const int pivoting = 1;
    int *np = malloc(sizeof(int));
    double **A;
    
    printf("\n");
    printf("================================\n");
    printf("======Gaussian Elimination======\n");
    printf("================================\n");
    printf("\n");
    A = parseSource(np);
    
    
    
    return -1;
}

Matrix parseSource(int *np){
    int i, n=0;
    double x;
    char choice, voodoo;
    double **mat;
    FILE *fileP;
    
    printf("Do you want to parse Default File: ");
    printf("`Source/GaussElimMatrix.txt`? (y/n)");
    scanf("%c", &choice);
    scanf("%c", &voodoo);
    
    if (choice == 'y') {
        fileP = fopen("Source/GaussElimMatrix.txt", "r");
        fscanf(fileP, "%d", &n);
        
        mat = allocQMatrix(n);
        
        for (i=0; i<n*n; i++){
            fscanf(fileP, "%lf", &x);
            mat[i/n][i%n] = x;
        }
    } else {
        printf("Inserisci la dimensione della matrice: ");
        scanf("%d", &n);
        
        mat = allocQMatrix(n);
        
        for (i=0; i<n*n; i++){
            printf("Inserici l'elemento A[%d][%d]: ", i/n, i%n);
            scanf("%lf", &x);
            mat[i/n][i%n] = x;
        }
    }
    
    np[0] = n;                                                                  ////??
    
    printf("\n======Data Reading Complete======\n\n");
    
    printf("n = %d\n", *np);
    printf("La matrice A parsata è:\n");
    printQMatrix(*np, mat);
    return mat;
}


