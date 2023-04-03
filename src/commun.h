#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

pokemon_t * createPkmDatabase(int taille);


void drawCases(SDL_Renderer *renderer, int x, int y, int width, int height, int rows, int cols);

/*void ras(){
    printf("Le code fonctionne correctement !\n");
}

void waiting(int time){
    sleep(time);
    system("cls");system("clear");
}*/

#endif
