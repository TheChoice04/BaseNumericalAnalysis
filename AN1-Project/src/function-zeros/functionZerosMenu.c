/*
 *  functionZerosMenu.c
 *
 *  Created on: 13 nov 2018
 *      Author: Elia Onofri
 */

#include "an1.function-zeros.h"

int functionZerosMenu();

/** functionZerosMenu *****************************************************
 *
 *	This function is meant to be a menu to choose between the Iterative
 *	 algorithms for the search of a zero of a function.
 *
 *	@return int exit code:
 *	  `0` : Correct outcome
 *	  `1` : Aborted
 *	  `3` : Wrong Method Choosing
 *
 *************************************************************************/

int functionZerosMenu(){
	int c;              // choicer
	int ans;            // exit-code
	double a, b;		// left and right margins (Bisection, Chord)
	double e;			// error range
	double x0;          // starting point of the method (Newton, Newton Quotient, Secantes)
	double x1;          // following point of the method (Secantes)
	double h;           // fixed increment for newton quotient method (Newton Quotient)

	double (*f)(double);     // function pointer
	double (*df)(double);    // derivative pointer

	selectFunction(&f, &df);

	printf("You can choose one of the following:\n");
	printf(" - type `1` to Bisection;\n");
	printf(" - type `2` to Chord;\n");
	printf(" * type `3` to Muller;\n");
	printf(" - type `4` to Newton;\n");
	printf(" - type `5` to Newton Quotient;\n");
	printf(" - type `6` to Secantes;\n");
	printf(" - type `7` to Steffensen;\n");
	printf(" - type `8` to execute them all and compare the answers!;\n");
	printf(" - type `0` to quit.\n");

	c = scanInt(0, 8);
	printf("\n\n");

	if (c == 1 || c == 2 || c == 8){
		printf("Type in the left and the right initialization:\n>> ");
		scanf("%lf %lf", &a, &b);
	}
	if (c == 2 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8){
		printf("Type in the initial point:\n>> ");
		scanf("%lf", &x0);
	}
	if (c == 6 || c == 8){
		printf("Type in the second point:\n>> ");
		scanf("%lf", &x1);
	}
	if (c == 5 || c == 8){
		printf("Type in the fixed increment for the quotient:\n>> ");
		scanf("%lf", &h);
	}
	if (c == 0){
		printf("Correctly aborted\n");
		return 1;
	}

	printf("Type in the error range:\n>> ");
	scanf("%lf", &e);

	switch (c) {
	case 1:
		ans = bisection(a, b, e, f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/bisection.gp");
		}
		break;

	case 2:
		ans = chord(a, b, x0, e, f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/chord.gp");
		}
		break;

		/*	case 3:
		ans = muller(f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/muller.gp");
		}
		break;
		 */
	case 4:
		ans = newton(x0, e, f, df);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/newton.gp");
		}
		break;

	case 5:
		ans = newtonQuotient(x0, h, e, f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/newtonQuotient.gp");
		}
		break;

	case 6:
		ans = secantes(x0, x1, e, f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/secantes.gp");
		}
		break;

	case 7:
		ans = steffensen(x0, e, f);
		if (ans == 0 || ans == 2){
			gnuplot("function-zeros/steffensen.gp");
		}
		break;

	case 8:
		printf("\n\n\nExecuting Bisection method...\n\n");
		bisection(a, b, e, f);

		printf("\n\n\nExecuting Chord method...\n\n");
		chord(a, b, x0, e, f);

		//printf("\nExecuting  method...\n\n");
		//ans = exeMuller(f);

		printf("\n\n\nExecuting Newton method...\n\n");
		newton(x0, e, f, df);

		printf("\n\n\nExecuting Newton Quotient method...\n\n");
		newtonQuotient(x0, h, e, f);

		printf("\n\n\nExecuting Secantes method...\n\n");
		secantes(x0, x1, e, f);

		printf("\n\n\nExecuting Steffensen method...\n\n");
		steffensen(x0, e, f);

		gnuplot("function-zeros/allMethods.gp");

		break;

	case 0:
		printf("Aborted\n");
		return 1;

	default:
		printf("ERROR: the method has not been encoded yet.\n");
		return 3;
	}

	return 0;
}

