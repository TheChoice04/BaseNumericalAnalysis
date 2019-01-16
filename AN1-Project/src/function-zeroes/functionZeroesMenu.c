//
//  functionZeroesMenu.c
//  ProjectManager
//
//  Created by Elia Onofri on 13/11/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

#include "an1.function-zeroes.h"

int selectIterativeMethod();
int selectFunction();
int exeAll();

/**
 * This function is meant to be a menu to choose between the Iterative
 *  algorithms for the search of a zero of a function.
 *
 * @return int exit code:
 *      `0` : Correct outcome
 *      `1` : Aborted
 *      `2` : Wrong Function Choosing
 *      `3` : Wrong Method Choosing
 */

int functionZeroesMenu(){
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
		result = exeChord(f);
		break;

	case 3:
		//result = exeMuller(f);
		break;

	case 4:
		result = exeNewton(f, df);
		break;

	case 5:
		result = exeNewtonQuotient(f);
		break;

	case 6:
		result = exeSecantes(f);
		break;

	case 7:
		result = exeSteffensen(f);
		break;

	case 8:
		result = exeAll(f, df);
		break;

	case 0:
		printf("Aborted\n");
		return 1;

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
	printf(" - type `2` to Chord;\n");
	printf(" - type `3` to Muller (NY);\n");
	printf(" - type `4` to Newton;\n");
	printf(" - type `5` to Newton Quotient;\n");
	printf(" - type `6` to Secantes;\n");
	printf(" - type `7` to Steffensen;\n");
	printf(" - type `8` to execute them all and compare!;\n");
	// Insert more choices here...
	printf(" - type `0` to quit.\n\n");

	printf("Make your choice: ");
	scanf("%d", &c);
	printf("\n\n");

	return c;
}

int exeAll(double (*f)(double), double (*df)(double)){
	double e;
	double a, b;
	double x, x2;
	double h;

	printf("Type in the error range: ");
	scanf("%lf", &e);

	printf("\n#---Bisection--Chord---#\n Type in the left and the right initialization: ");
	scanf("%lf %lf", &a, &b);

	printf("\n#---Chord--Newton--NewtonQuotient--Secantes--Steffensen---#\n Type in the initial point: ");
	scanf("%lf", &x);

	printf("\n#---Secantes---#\n Type in the second point: ");
	scanf("%lf", &x2);

	printf("\n#---NewtonQuotient---#\n Type in the incremental value: ");
	scanf("%lf", &h);

	printf("\n\n\nExecuting Bisection method...\n\n");
	bisection(a, b, e, f);

	printf("\n\n\nExecuting Chord method...\n\n");
	chord(a, b, x, e, f);

	//printf("\nExecuting  method...\n\n");
	//result = exeMuller(f);

	printf("\n\n\nExecuting Newton method...\n\n");
	newton(x, e, f, df);

	printf("\n\n\nExecuting Newton Quotient method...\n\n");
	newtonQuotient(x, h, e, f);

	printf("\n\n\nExecuting Secantes method...\n\n");
	secantes(x, x2, e, f);

	printf("\n\n\nExecuting Steffensen method...\n\n");
	steffensen(x, e, f);
	return 0;
}

