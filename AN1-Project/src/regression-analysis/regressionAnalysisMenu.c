/*
 * regressionAnalysisMenu.c
 *
 *  Created on: 13 feb 2019
 *      Author: Elia Onofri
 **
 *	Macros used:
 *	 fprintPoint(p, x, fx) -> fprintf(p, ""flfpf" "flfpf"\n", x, fx)
 *	 Matrix -> double**
 */


#include "an1.regression-analysis.h"

int regressionAnalysisMenu();


/** regressionAnalysisMenu ************************************************
 *
 * This function is meant to be a menu to choose between the regression
 *  analysis algorithms to approximate a given function.
 *
 * @return int exit code:
 *      `0` : Correct outcome.
 *      `3` : Method not encoded yet.
 *
 *************************************************************************/

int regressionAnalysisMenu(){
	int c;              // choicer
	int i;              // counter
	int n;              // number of points
	int ans;            // regression exit-code
	int ord;            // order of the regression
	Matrix P;           // points matrix
	FILE *fileP;        // Points output file pointer

	parseCloud(&P, &n);

	printf("The cloud parsed is:\n");
	printMatrix(P, n, 2);

	fileP = fopen("results/regression-analysis/dataCloud.txt", "w");

	if (fileP == NULL){
		printf("ERROR: can't open `results/regression-analysis/dataCloud.txt` in writing mode.\n");
		exit(1);
	}

	for (i = 0; i < n; i++)
		fprintPoint(fileP, P[i][0], P[i][1]);

	fclose(fileP);

	printf("You can choose one of the following Regression Analysis Methods:\n");
	printf(" - type `1` to first order least squares method;\n");
	printf(" * type `2` to higher order least squares method.\n");
	c = scanInt(1, 2);

	switch (c) {
	case 1:
		ans = leastSquare(P, n, 1);
		if (ans == 0)
			gnuplot("regression-analysis/leastSquaresLine.gp");

		break;

	case 2:
		printf("Type in the order of the least square method you want to evaluate:\n");
		ord = scanInt(1, 100);
		ans = leastSquare(P, n, ord);
		if (ans == 0)
			gnuplot("regression-analysis/leastSquares.gp");

		break;

	default:
		printf("WARNING: the chosen method has not been encoded yet.\n");
		return 3;
	}

	return 0;
}
