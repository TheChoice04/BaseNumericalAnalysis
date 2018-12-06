//
//  iterativeMenu.c
//  ProjectManager
//
//  Created by Elia Onofri on 13/11/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#include "an1.iteratives.h"

int selectIterativeMethod();
int selectFunction();

/**
 * This function is meant to be a menu to choose between the Iterative
 *  algorithms for the search of a zero of a function.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 */

int iterativeMenu(){
	int c;
	double result;

	double (*f)(double);
	double (*df)(double);
	c = selectFunction();
	switch (c) {
	case 1:
		f = &samplef1;
		df = &dsamplef1;
		break;

	case 2:
		f = &samplef2;
		df = &dsamplef2;
		break;

	default:
		return 2;
	}

	c = selectIterativeMethod();
	switch (c) {
	case 1:
		result = exeBisection(f);
		break;

	case 2:
		//result = exeFixedPoint(f);
		break;

	case 3:
		result = exeChord(f);
		break;

	case 4:
		//result = exeSecant(f);
		break;

	case 5:
		result = exeNewton(f, df);
		break;

	case 6:
		//result = exeQNewton(f);
		break;

	case 0:
		printf("Aborted\n");
		break;

	default:
		printf("ERROR: no function for the choice made.");
		return 3;
	}

	return 0;
}


int selectIterativeMethod(){
	int c;
	printf("You can choose one of the following:\n");
	printf(" - type `1` to Bisection;\n");
	printf(" - type `2` to Fixed Point (NY);\n");
	printf(" - type `3` to Chord;\n");
	printf(" - type `4` to Secanti (NY);\n");
	printf(" - type `5` to Newton;\n");
	printf(" - type `6` to Near Newton (NY);\n");
	// Insert more choices here...
	printf(" - type `0` to quit.\n\n");

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	return c;
}

int selectFunction(){
	int c;

	printf("Choose one of the following functions:\n");
	printf(" - type '1' to choose: (e^x)-1\n");
	printf(" - type '2' to choose: x/2-sin(x)\n");
	// Insert more choices here...

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	return c;
}

