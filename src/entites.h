/**
 * @file entites.h
 * @author Gouffier Anthony
 * @brief fichier qui contient les structures
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENTITES_H
#define ENTITES_H

#include "SDL.h"
#include <stdbool.h>

//#include "commun.h"
// #include "boutique.h"

typedef bool objet;

typedef struct pokemon_s
{
    int id;
    int dresseur;
    char name[64];
    /*Stats*/
    int pv_max;
    int pv;
    int total;
    float att;
    float def;
    float attspe;
    float defspe;
    float spd;
    int range;
    /*autre*/
    char classe[20];
    int rarete;
    int stade;
    bool alive;
    /*partie graphique*/
    SDL_Surface * imgSurface;
    /*coordonne*/
    int x , y;
}pokemon_t;


typedef struct boutique_s
{
  pokemon_t * deck[5];
}boutique_t;


typedef struct pos_s{
  int y;
  int x;
}pos_t;

/*PROTOTYPE DES FONCTION DE GENERER DATABASE*/
pokemon_t* createPkmDatabase(int,int);
pokemon_t* genererationDatabase();
//pokemon_t* initialiserPkm(pokemon_t* );
pokemon_t initialiserPkm();
void printPkm(pokemon_t );
void afficherEquipe(pokemon_t *,int );


#endif