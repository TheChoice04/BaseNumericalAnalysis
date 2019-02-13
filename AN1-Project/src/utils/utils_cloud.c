/*
 * utils_cloud.c
 *
 *  Created on: 13 feb 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 *	 Matrix -> double**
 *	 MAX_POINTs
 */


#include "an1.utils.h"

int parseCloud(Matrix* Pp, int *np);


/** parseCloud ************************************************************
 *
 *	This method parse a cloud data point:
 *	  - from the default file;
 *	  - from a particular file;
 *	  - with random values;
 *	  - from keyboard input.
 *
 *	The file must be built according to the following convention:
 *	  - the number of data points `n` (int);
 *	  - a list of the points `x y` (double).
 *	Everything after those numbers will be ignored so it could be used
 *	 as comments.
 *
 *	@param *Pp Matrix: The pointer to the points matrix (will be created).
 *	@param *np int: pointer to the integer field of the points number.
 *
 *	@return int exit-code:
 *	  `0` : Correct outcome.
 *	  `1` : Some error occurred.
 *
 *************************************************************************/

int parseCloud(Matrix* Pp, int *np){
	int choice;         // choicer
	int i;              // counter
	int n;              // number of points
	double minX, maxX;  // min_x and max_x random value
	double minY, maxY;  // min_y and max_y random value
	char filepath[256]; // file path to .txt
	FILE *fileP;        // input file pointer
	Matrix P = NULL;    // Points matrix

	printf("You can choose one of the following input methods for the data cloud:\n");
	printf(" - type `1` to parse the default data cloud `source/DefaultDataCloud.txt`;\n");
	printf(" * type `2` to parse a `.txt` file;\n");
	printf(" - type `3` to random parse the cloud;\n");
	printf(" - type `4` to manually type in the cloud (discouraged).\n");
	choice = scanInt(1, 4);

	switch (choice){
	case 1:
		fileP = fopen("source/DefaultDataCloud.txt", "r");
		if (fileP == NULL){
			printf("ERROR: can't open the source file in reading mode.\n");
			exit(1);
		}

		// Scan the Source
		fscanf(fileP, "%d", &n);
		break;

	case 2:
		printf("Please specify a file-path.\n>> ");
		fgets(filepath, 256, stdin);
		fileP = fopen(filepath, "r");
		if (fileP == NULL){
			printf("ERROR: can't open the source file in reading mode.\n");
			exit(1);
		}

		// Scan the Source
		fscanf(fileP, "%d", &n);
		break;

	case 3:
	case 4:
		printf("Choose the number of points to approximate.\n");
		n = scanInt(2, MAX_POINTs);
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;
	}

	P = allocMatrix(n, 2);

	switch (choice){
	case 1:
	case 2:
		for (i = 0; i < n; i++)
			fscanf(fileP, "%lf %lf", &P[i][0], &P[i][1]);

		fclose(fileP);
		break;

	case 3:	// Random
		printf("Type in minimum and maximum `x` values for your cloud:\n>> ");
		scanf("%lf %lf", &minX, &maxX);
		ln;
		printf("Type in minimum and maximum `y` values for your cloud:\n>> ");
		scanf("%lf %lf", &minY, &maxY);
		ln;

		for (i = 0; i < n; i++){
			P[i][0] = Random(minX, maxX);
			P[i][1] = Random(minY, maxY);
		}
		break;

	case 6:	// Manual
		for (i = 0; i < n; i++){
			printf("Type in the x and the y value for the %d-th point of the cloud:\n>> ", (i+1));
			scanf("%lf %lf", &P[i][0], &P[i][1]);
		}
		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;

	}

	*Pp = P;
	*np = n;

	return 0;
}
