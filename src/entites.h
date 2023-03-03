#include "commun.h"

typedef bool objet;

typedef struct pokemon_s
{
    int id;
    int dresseur;
    char * name;
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
    void * img;
    /*coordonne*/
    int x , y;
}pokemon_t;

typedef struct player_s
{
    int id;
    int hp;
    int niveau;
    pokemon_t * team;
    objet * objListe ;
    /*status*/
    int money;
    int interest;
    bool alive;
}player_t;
