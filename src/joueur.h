#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "entites.h"
#include "carte.h"

typedef struct player_s{   
    int id;
    char nom[16];
    int lvlcap[10];
    int xp;
    int hp;
    int niveau;
    pokemon_t team[10];
    //objet objListe[10] ;
    //boutique_t boutique;
    int money;
    int interest;
    bool alive;
}player_t;

void acheterCarte(player_t* , carteBoutique*  ,pokemon_t* );
void createPlayer(player_t* , int);
void acheterNiveauXP(player_t*);
void stat_player(player_t* );


#endif