/*
 * an1.regression-analysis.h
 *
 *  Created on: 13 feb 2019
 *      Author: Elia Onofri
 */

#ifndef SRC_REGRESSION_ANALYSIS_AN1_REGRESSION_ANALYSIS_H_
#define SRC_REGRESSION_ANALYSIS_AN1_REGRESSION_ANALYSIS_H_

#include "../utils/an1.utils.h"

//
//	interpolationMenu.c
//

int regressionAnalysisMenu();

//
//	regression analysis functions
//

int leastSquare(Matrix P, int n, int ord);
int leastSquareLine(Matrix P, int n);



#endif /* SRC_REGRESSION_ANALYSIS_AN1_REGRESSION_ANALYSIS_H_ */
