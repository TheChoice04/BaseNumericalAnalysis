/*
 * directMenu.c
 *
 *  Created on: 16 nov 2018
 *      Author: Elia
 */

#include "an1.direct.h"

int selectDirectMethod();

/**
 * This function is meant to be a menù to choose between the Iterative
 *  algorithms for the search of a zero of a function.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 */

int directMenu(){
    int c;
    int ans;



    c = selectDirectMethod();
    switch (c) {
        case 1:
            ans = gaussianElimination();
            break;

        case 0:
            printf("Aborted\n");
            break;

        default:
            return 3;
    }

    return 0;
}


int selectDirectMethod(){
    int c;
    printf("You can choose one of the following:\n");
    printf(" - type `1` to Gaussian Elimination;\n");
    printf(" - type `2` to LU factorization (doolittle) (NY);\n");
    printf(" - type `3` to LU factorization (cholesky) (NY);\n");
    printf(" - type `4` to QR factorization (NY);\n");
    // Insert more choiches here...
    printf(" - type `0` to quit.\n\n");

    printf("Make your choice: ");
    scanf("%d", &c);
    printf("\n\n");

    return c;
}
