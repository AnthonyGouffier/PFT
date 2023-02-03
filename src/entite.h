#include "commun.h"

typedef objet;

typedef struct pokemon_s
{
    char * name;
    /*Stats*/
    int pv_max;
    int pv;
    float att;
    float def;
    //float attspe;
    //float defspe;
    float spd;
    int range;
    /*autre*/
    int rarete;
    bool alive;
    /*partie graphique*/
    void * img;
    /*coordonne*/
    int x,y;
}pokemon_t;

typedef struct player_s
{
  char * name;
    int hp;
    int level;
    pokemon_t *team;
    objet * objListe ;
    /*status*/
    int money;
    int interest;
    bool alive;
    //boutique_t boutique;


}player_t;
