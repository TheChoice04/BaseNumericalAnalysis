//
//  mainMenu.c
//  AN410 Project Manager
//
//  Created by Elia Onofri on 02/10/18.
//  Copyright © 2018 Elia Onofri. All rights reserved.
//

/**
 *  This function is a mere method to choose between the function
 *    prepared during the course of AN410 (A.A.1819).
 *
 *  @return int exit-code:
 *      `0` : correct outcome
 *      `1` : wrong exit from the main menu
 *      `2` : wrong attempts in main menu more than MAX_ATTEMPTs
 *      `9` : manual exit.
 */


#include "an1.h"

int selectTask();

int mainMenu() {
    const int MENU_MAX_ATTEMPTs = 5;
    int i = 0, flag = 1;
    char choice;
    printf("Hi There!\n");
    printf("Please choose one of the following:\n");

    while (i <= MENU_MAX_ATTEMPTs && flag == 1) {
        choice = selectTask();
        switch (choice) {
            case 1:
            	directMenu();
                i=0;
                break;

            case 2:
            	i=0;
            	break;

            case 3:
                functionZeroesMenu();
                i=0;
                break;

            case 4:

            	i=0;
            	break;

            case 5:

            	i=0;
            	break;

            case 0:
                flag = 0;
                break;

            default:
                printf("No choices associated to %c.\n", choice);
                i++;
                if (i > MENU_MAX_ATTEMPTs){
                    flag = 2;
                    printf("==========================\n");
                    printf("======To Much Errors======\n");
                    printf("==========================\n");
                }
                break;
        }
    }
    return flag;
}


int selectTask(){
    int c;
    printf("You can choose one of the following:\n");
    printf(" - type `1` to solve a linear system via direct method;\n");
    printf(" - type `2` to solve a linear system via iterative method;\n");
    printf(" - type `3` to find a zero of a function\n");
    printf(" - type `4` to approximate a function via interpolation\n");
    printf(" - type `5` to approximate a function via least squares method.\n");
    // Insert more choices here...
    printf(" - type `0` to quit.\n");
    
    printf("Make your choice: ");
    scanf("%d", &c);
    printf("\n\n");
    
    return c;
}
