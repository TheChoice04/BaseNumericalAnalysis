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
 *      `1` : wrong exit from the main menù
 *      `2` : wrong attempts in main menù more than MAX_ATTEMPTs
 *      `9` : manual exit.
 */


#include "mainHeader.h"

char makeChoice();

int mainMenu() {
    const int MAX_ATTEMPTs = 5;
    int i = 0, flag = 1;
    char choice;
    printf("Hi There!\n");
    printf("Please choose one of the following:\n");
    
    while (i <= MAX_ATTEMPTs && flag == 1) {
        choice = makeChoice();
        switch (choice) {
            case 'g':
                gaussianElimination();
                i=0;
                break;
            case 'q':
                flag = 0;
                break;
            default:
                printf("No choices associated to %c.\n", choice);
                i++;
                if (i > MAX_ATTEMPTs){
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


char makeChoice(){
    char c;
    printf("You can choose one of the following:\n");
    printf(" - press `g` to Gaussian Elimination;\n");
    // Insert more choiches here...
    printf(" - press `q` to quit.\n");
    
    printf("Make your choice: ");
    scanf("%c", &c);
    char voodoo;
    scanf("%c", &voodoo); //THIS IS TO IGNORE `\n` char THAT COMES OUT FROM INPUT.
    printf("\n\n");
    
    return c;
}
