#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "entites.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

void generer_carteV1(pokemon_t* , SDL_Renderer* , int, int);


/*PROTOTYPE DES FONCTION DE GENERER DATABASE*/
pokemon_t* createPkmDatabase(int);
pokemon_t* genererationDatabase();
pokemon_t* initialiserPkm(pokemon_t* );
void printPkm(pokemon_t );
void afficherEquipe(pokemon_t *,int );

/*Creer un bouton du shop dynamiquement*/
SDL_Rect genererCartePokemon(SDL_Renderer* renderer, int x, int y, int largeur, int hauteur, pokemon_t* pokemon) ;

/*Fonctions pratiques*/
int initialiserModules();

void drawCases(SDL_Renderer *renderer, int, int, int, int, int, int);

char* int_to_string(int);

/*void ras(){
    printf("Le code fonctionne correctement !\n");
}

void waiting(int time){
    sleep(time);
    system("cls");system("clear");
}*/



#endif
