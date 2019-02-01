/*
 * utils_utility.c
 *
 *  Created on: 19 gen 2019
 *      Author: Elia
 *
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 MAX_ERRs
 */


#include "an1.utils.h"

int scanInt(int min, int max);
double scanDouble(double min, double max);


/** scanInt ***************************************************************
 *
 *	This method is used to read an integer from system.in within the range
 *	 defined `[min, max]`.
 *	After `MAX_ERRs` errors the program exit with error.
 *
 *	@param min int: minimum int to be parsed;
 *	@param max int: maximum int to be parsed;
 *
 *	@return int the choice `c` the user made.
 *
 *************************************************************************/

int scanInt(int min, int max){
	int i;              // counter
	int c;              // choice

	for (i = 1; i <= MAX_ERRs; i++){
		printf(">> ");
		scanf("%d", &c);
		ln;
		if (c < min || c > max){
			printf("WARNING: The value is not in the current range [%d, %d].\n", min, max);
			printf("         Please insert a valid value.               (%d)\n", MAX_ERRs-i);
		} else {
			ln;
			return c;
		}
	}
	exit(9);
}


/** scanDouble ************************************************************
 *
 *	This method is used to read an double from system.in within the range
 *	 defined `[min, max]`.
 *	After `MAX_ERRs` errors the program exit with error.
 *
 *	@param min double: minimum double to be parsed;
 *	@param max double: maximum double to be parsed;
 *
 *	@return double: the choice `c` the user made.
 *
 *************************************************************************/

double scanDouble(double min, double max){
	int i;              // counter
	double c;           // choice

	for (i = 1; i <= MAX_ERRs; i++){
		printf(">> ");
		scanf("%lf", &c);
		ln;
		if (c < min || c > max){
			printf("WARNING: The value is not in the current range [%lf, %lf].\n", min, max);
			printf("         Please insert a valid value.               (%d)\n", MAX_ERRs-i);
		} else {
			ln;
			return c;
		}
	}
	exit(9);
}
