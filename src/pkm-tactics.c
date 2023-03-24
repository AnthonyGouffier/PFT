#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "entites.h"
#include "boutique.h"

	int main(){

	srand( time( NULL ) );

	//pokemon_t *database=createPkmDatabase(3);


  player_t player;
  player.niveau = 3;
  /*player.name = "sacha";*/

	pokemon_t * database[2];


  // tier 1
  pokemon_t * poke1_tier1;
  pokemon_t * poke2_tier1;

	poke1_tier1->rarete = 1;
	poke2_tier1->rarete = 1;

	//poke1_tier1->name = "Pikachu";
	//poke2_tier1->name = "Chenipan";

	database[0] = poke1_tier1;
	database[1] = poke2_tier1;



	//affichertableau(database, 1);

  // tier 2
  /*pokemon_t poke1_tier2;
  pokemon_t poke2_tier2;
  poke1_tier2.name = "poke1 tier2";
  poke1_tier2.rarete = 1;
  poke2_tier2.name = "poke2 tier2";
  poke2_tier2.rarete = 1;

  // tier 3
  pokemon_t poke1_tier3;
  pokemon_t poke2_tier3;
  poke1_tier3.name = "poke1 tier3";
  poke1_tier3.rarete = 2;
  poke2_tier3.name = "poke2 tier3";
  poke2_tier3.rarete = 2;

  // tier 4
  pokemon_t poke1_tier4;
  pokemon_t poke2_tier4;
  poke1_tier4.name = "poke1 tier4";
  poke1_tier4.rarete = 3;
  poke2_tier4.name = "poke2 tier4";
  poke2_tier4.rarete = 3;

  // tier 5
  pokemon_t poke1_tier5;
  pokemon_t poke2_tier5;
  poke1_tier5.name = "poke1 tier5";
  poke1_tier5.rarete = 4;
  poke2_tier5.name = "poke2 tier5";
  poke2_tier5.rarete = 4;*/


  //printf("Niveau joueur : %i\nNom joueur : %s\n", player.level, player.name);

  generate(&player, database);

}
