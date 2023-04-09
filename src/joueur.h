#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include "entites.h"

typedef struct player_s{   
    int id;
    char nom[16];
    int lvlcap[10];
    int xp;

    int hp;

    int niveau;
    pokemon_t *team;
    objet * objListe ;
    //boutique_t boutique;
    /*status*/
    int money;
    int interest;
    bool alive;
}player_t;


void createPlayer(player_t*);
void acheterNiveauXP(player_t*);
void stat_player(player_t* );


#endif