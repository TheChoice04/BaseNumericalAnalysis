/*
 * directMenu.c
 *
 *  Created on: 16 nov 2018
 *      Author: Elia
 */

#include "an1.direct.h"


/**
 * This function is meant to be a menu to choose between the Direct
 *  algorithms to solve the linear systems.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 */

int directMenu(){
	int c;
	int ans;

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Gaussian Elimination;\n");
	printf(" * type `2` to LU factorization;\n");
	printf(" * type `3` to LU factorization;\n");
	printf(" * type `4` to QR factorization;\n");
	printf(" - type `0` to quit.\n\n");

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

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
