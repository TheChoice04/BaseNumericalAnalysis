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
	int i, c;

	for (i = 1; i <= MAX_ERRs; i++){
		printf(">> ");
		scanf("%d", &c);
		ln;
		if (c < min || c > max){
			printf("WARNING: The value is not in the current range [%d, %d].\n", min, max);
			printf("         Please insert a valid value.               (%d)\n", MAX_ERRs-i);
		} else
			ln;
			return c;
	}
	exit(9);
}
