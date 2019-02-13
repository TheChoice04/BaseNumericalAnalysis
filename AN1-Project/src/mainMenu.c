/*
 * MainMenu.c
 *
 *  Created on: 02 ott 2018
 *      Author: Elia Onofri
 */


#include "an1.h"

int mainMenu();


/** mainMenu **************************************************************
 *
 *	This function is a mere method to choose between the function
 *	 prepared during the course of AN410 (A.A.1819).
 *
 *	@return int exit-code:
 *	  `0` : correct outcome
 *	  `1` : wrong exit from the main menu
 *	  `9` : manual exit.
 *
 *************************************************************************/

int mainMenu() {
	int flag = 1;       // flag that is one till user want to exit.
	char choice;        // choicer

	while (flag == 1) {

		printf("You can choose one of the following:\n");
		printf(" - type `1` to solve a linear system via direct method;\n");
		printf(" - type `2` to solve a linear system via iterative method;\n");
		printf(" - type `3` to find a zero of a function\n");
		printf(" - type `4` to approximate a function via interpolation\n");
		printf(" - type `5` to approximate a function via least squares method.\n");
		printf(" - type `0` to quit.\n");

		choice = scanInt(0, 5);

		printf("\n\n");

		switch (choice) {
		case 1:
			directMenu();
			break;

		case 2:
			iterativeMenu();
			break;

		case 3:
			functionZerosMenu();
			break;

		case 4:
			interpolationMenu();
			break;

		case 5:
			regressionAnalysisMenu();
			break;

		case 0:
			flag = 0;
			break;

		default:
			printf("No choices associated to %c.\n", choice);
			break;
		}
	}
	return flag;
}
