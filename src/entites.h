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

typedef struct player_s
{
    int id;
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

typedef struct boutique_s
{
  pokemon_t * deck[5];
}boutique_t;


typedef struct pos_s{
  int y;
  int x;
}pos_t;
