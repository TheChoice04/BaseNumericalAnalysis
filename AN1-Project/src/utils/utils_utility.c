/*
 * utils_utility.c
 *
 *  Created on: 19 gen 2019
 *      Author: Elia
 */

#include "an1.utils.h"

/**
 * This method is used to read an integer from system.in within the range
 *  defined [min, max].
 * After MAX_ERRs errors the program exit with error.
 *
 * @param min int: minimum int to be parsed;
 * @param max int: maximum int to be parsed;
 */
int scanInt(int min, int max){
	int i, x;

	for (i = 1; i <= MAX_ERRs; i++){
		printf(">> ");
		scanf("%d", &x);
		if (x < min || x > max){
			printf("WARNING: The value is not in the current range [%d, %d].\n", min, max);
			printf("         Please insert a valid value.               (%d)\n", MAX_ERRs-i);
		} else
			return x;
	}
	exit(9);
}
