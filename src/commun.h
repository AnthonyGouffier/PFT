/**
 * @file commun.h
 * @author Gouffier Anthony, Deletang Elie, Gaumont Mael, Gérome vivien
 * @brief contient les prototys
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef COMMUN_H
#define COMMUN_H

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
/*inclusion SDL*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/*Fonctions pratiques*/
void pressAnyKeyToContinue();
int initialiserModules();
void drawCases(SDL_Renderer *renderer, int, int, int, int, int, int);
char* int_to_string(int ) ;

/*void ras(){
    printf("Le code fonctionne correctement !\n");
}

void waiting(int time){
    sleep(time);
    system("cls");system("clear");
}*/

#endif