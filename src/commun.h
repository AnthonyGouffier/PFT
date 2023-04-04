#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

<<<<<<< HEAD
=======
#include "entites.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

/*PROTOTYPE DES FONCTION DE GENERER DATABASE*/
pokemon_t* createPkmDatabase(int);
pokemon_t* genererationDatabase();


void drawCases(SDL_Renderer *renderer, int, int, int, int, int, int);

>>>>>>> origin/SDL
/*void ras(){
    printf("Le code fonctionne correctement !\n");
}

void waiting(int time){
    sleep(time);
    system("cls");system("clear");
}*/

#endif
