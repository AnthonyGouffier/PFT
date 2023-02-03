#include "commun.h"
#include "entite.h"

int rarete[8][5] = // stocke la probabilité de chaque tier de pokemon pour chaque niveau du joueur
{
  // {tier1, tier2, tier3, tier4, tier4, tier5}
  {100, 0, 0, 0, 0},    // lvl 1,2      indice => 0
  {70, 25, 5, 0, 0},    // lvl 3        indice => 1
  {50, 35, 15, 0, 0},   // lvl 4        indice => 2
  {35, 35, 25, 5, 0},   // lvl 5        indice => 3
  {25, 35, 30, 10, 0},  // lvl 6        indice => 4
  {20, 30, 33, 15, 2},  // lvl 7        indice => 5
  {15, 25, 35, 24, 6},  // lvl 8        indice => 6
  {10, 15, 30, 30, 15} // lvl 9        indice => 7

}

typedef struct boutique_s
{

  pokemon_t * [5];

} boutique_t;

void refresh(player_t * player)
{
  int indice = player->level = 1 ? 2 : player->level; // recupere un indice correspondant au niveau du joueur

  tab[5] rare = rarete[level-2]; // selection la ligne du tableau correspondant à la rareté

  for(int i = 0; i < 5; i++)
  {
    int indice_rarete = 4;
    r = rand() % 100 + 1; // genère un nombre r entre 0 et 100

    while(r < rarete[indice][indice_rarete])
    {
      indice_rarete--;
    }

    // sélectionner un pokemon aléatoire avec la rarete : indice_rarete
    // mettre le pokemon dans le tableau de la boutique à l'indice : i


  }

}
