//
//  util_Matrix.c
//  AN410 ProjectManager
//
//  Created by Elia Onofri on 09/10/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#include "mainHeader.h"

/**
 *  Here matrix are allocated by rows so mat[i][j] is the jth element
 *    of the i-th row.
 *
 *
 *
 */

Vector allocVector(int);
Matrix allocMatrix(int, int);
Matrix allocQMatrix(int);

Vector multMV(int, int, Matrix, int, Vector);
Matrix multMM(int, int, Matrix, int, int, Matrix);

void printVector(int, Vector);
void printMatrix(int, int, Matrix);
void printQMatrix(int, Matrix);



//
//  Allocate Operation
//


Vector allocVector(int n){
    return allocate(n, double);
}

Matrix allocMatrix(int m, int n){
    int i;
    Matrix mat;
    mat = allocate(m, double*);
    for (i = 0; i<m; i++)
        mat[i] = allocVector(n);
    return mat;
}

Matrix allocQMatrix(int n){
    return allocMatrix(n, n);
}

//
//  Algebraic Operation
//

Vector multMV(int m, int n, Matrix mat, int n1, Vector v){
    Vector r;
    int i, j;
    double sum;
    
    if (n != n1)
        printf("ERROR: matrix multiplication only works with (mxn)(nxk)=(mxk)");
    else {
        r = allocate(n, double);
        for (i=0; i<m; i++){
            sum = 0.0;
            for (j=0; j<n; j++)
                sum += (mat[i][j] * v[j]);
            r[i] = sum;
        }
    }
    return r;
}

Matrix multMM(int m, int n, Matrix mat, int m1, int n1, Matrix mat1){
    int i, j, k;
    double sum;
    Matrix r;
    
    if (n != m1)
        printf("ERROR: matrix multiplication only works with (mxn)(nxk)=(mxk)");
    else {
        r = allocMatrix(m, n1);
        for (i=0; i<m; i++){
            for (j=0; j<n1; j++){
                sum = 0.0;
                for (k=0; k<n; k++)
                    sum += (mat[i][k] * mat1[k][j]);
                r[i][j] = sum;
            }
        }
    }
    return r;
}

//
//  Print Operation
//

void printVector(int n, Vector v){
    int i;
    for (i=0; i<n; i++){
        printf("\t%lf", v[i]);
    }
}

void printMatrix(int m, int n, Matrix mat){
    int i, j;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++)
            printf("\t%lf", mat[i][j]);
        ln;
    }
}

void printQMatrix(int n, Matrix mat){
    printMatrix(n, n, mat);
}
