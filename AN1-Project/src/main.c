/*
 * main.c
 *
 *  Created on: 3 ott 2018
 *      Author: Elia Onofri
 *
 **
 *	Macros used:
 *	 ln -> printf("\n")
 *	 Matrix -> double**
 *	 Vector -> double*
 *	 Random(x, y) -> (x + ((double) rand()/RAND_MAX)*(y-x))
 */


#include "an1.h"
#include "string.h"

int main();

/** main ******************************************************************
 *
 *	Main function.
 *	It only initialize the random seed and launch the main men§.
 *
 *	@return int code-error from mainMenu.
 *
 *************************************************************************/

int main(){
    hi;
    srand(time(NULL));
    printf("\n");
    return mainMenu();
}

