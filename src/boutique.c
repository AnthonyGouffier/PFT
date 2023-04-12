/**
 * @file boutique.c
 * @author Deletang Elie
 * @brief Programme qui tire et génère un pokémon qui vas pouvoir ensuite etre acheter
 * @version 0.1
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */


 #include <time.h>
 #include "boutique.h"

 int rarete[9][5] = // stocke la probabilité de chaque tier de pokemon pour chaque niveau du joueur
 {
   // {tier1, tier2, tier3, tier4, tier4, tier5}
   {100, 0, 0, 0, 0},    // lvl 1        indice => 0
   {100, 0, 0, 0, 0},    // lvl 2        indice => 1
   {70, 25, 5, 0, 0},    // lvl 3        indice => 2
   {50, 35, 15, 0, 0},   // lvl 4        indice => 3
   {35, 35, 25, 5, 0},   // lvl 5        indice => 4
   {25, 35, 30, 10, 0},  // lvl 6        indice => 5
   {20, 30, 33, 15, 2},  // lvl 7        indice => 6
   {15, 25, 35, 24, 6},  // lvl 8        indice => 7
   {10, 15, 30, 30, 15}  // lvl 9         indice => 8
 };

 /*

   ** structure database **

   [29 * 6, 22 * 5, 16 * 4, 12 * 3, 10 * 2]

   [tier1*nb_tier1,tier2*nb_tier2,tier3*nb_tier3,tier4*nb_tier4,tier5*nb_tier5] : size = taille

   generate random pokemon of tier n

   exemple tier 3 :

     start = nb_tier1 + nb_tier2
     end   = start + nb_tier3

     random = random(nb_tier3) + start

   exemple tier n:

     start = pour i de 0 à n-1 : start += nb_tier(i)
     end = start + nb_tier(n)

     random = random(nb_tier(n)) + start

 */

 int nbPokeTier[5]     = { 6,5,4,3,2 };     // nombre de pokemon différent pour chaque tier
 int nbRepliqueTier[5] = { 29,22,16,12,10}; // nombre de replique de chaque pokemon different pour chaque tier

 pokemon_t * tirerPokemon(int tier, pokemon_t * database)
 {

   int debut = 0;
   for(int i = 1;i < tier; i++)
   {
     debut+=nbPokeTier[i-1]*nbRepliqueTier[i-1];
   }

   printf("\ndebut : %d\n", debut);

   printf("\nmax : %d\n", nbPokeTier[tier-1] * nbRepliqueTier[tier-1]);


   int pok_pos = rand() % (nbPokeTier[tier-1] * nbRepliqueTier[tier-1]);


   printf("\nrand : %d\n", pok_pos);

   pok_pos+=debut;


   printf("\npos : %d\n", pok_pos);

   return &database[pok_pos];
 }

 void acheter(player_t * player, pokemon_t * pokemon, boutique_t * boutique)
 {
   if(player->money >= pokemon->rarete)
   {
     player->money-=pokemon->rarete;
     // supprimer le pokemon de la boutique
     // rajouter le pokemon au deck du joueur
     //player->team += pokemon;
   }
 }

 pokemon_t * genererBoutique(player_t * player, pokemon_t * database)
 {
   int level = (player->niveau);                 // recupere niveau du joueur
   int indice = level-1;                         // convertit le niveau du joueur en indice
   printf("indice : %i\n", indice);
   int drop = 0;

   pokemon_t * boutique = malloc(sizeof(pokemon_t) * 5);

   for(int i = 0; i < 5; i++)                    // pour les 5 pokemons tiré dans la boutique
   {
     printf("\n  [[ POKEMON %i ]] \n", i+1);

     int tier = 4;

     while(tier > 0)
     {
       drop = rand() % 101;                      // on génére un nombre entre 0 et 100
       if(rarete[indice][tier] > drop)           // Si le nombre générer est plus petit ou égal au taux de drop
       {
         break;                                  // Le tier courant est selectionné
       }
       tier--;                                   // Sinon on passe au tier d'en dessous
     }

     printf("\n  ** TIER **  %i\n", tier+1);

     boutique[i] = *tirerPokemon(tier+1, database); // on ajoute à la boutique le pokemon tiré aléatoirement avec le tier selectionné

   }


   for(int i = 0; i < 5; i++)
   {

     printf("|--------------------|\n");
     printf("|                    |\n");
     printf("|     (Pokemon%d)     |\n", i+1);
     printf("|  Nom: %s           \n", boutique[i].name);
     printf("|  Tier: %d          \n", boutique[i].rarete);
     printf("|                    |\n");
     printf("|--------------------|\n");
   }


   return boutique;
 }

 // clear && gcc -o bin/boutique src/boutique.c src/database.c ./src/fonction_SDL.c $(sdl2-config --cflags --libs) -lSDL2 -lSDL2_image -lSDL2_ttf && ./bin/boutique

 // clear && gcc -o bin/gif src/pkm-tactics.c ./src/CEV_gif.h ./src/CEV_gifDeflate.c ./src/CEV_gifDeflate.h ./src/CEV_gifToSurface.c ./src/CEV_gifToSurface.h ./src/CEV_gifUser.c $(sdl2-config --cflags --libs) -lSDL2 -lSDL2_image -lSDL2_ttf && ./bin/gif

/*
 int main(int argc, char* argv[])
 {
  srand( time( NULL ) );


   /*int pokemon_size = 1;
   pokemon_t * database = createPkmDatabase(pokemon_size);
   pokemon_t **liste = database;
   printf("Liste pokemons :\n");
   for(int i = 0; i < pokemon_size; i++)
   {
     printf(" name : %s \n rarete : %d \n\n", database->name, database->rarete);
     database++;
   }

   database = liste;

   // TEST FONCTION TIRER POKEMON
   for(int i = 0; i < pokemon_size; i++)
   {
     pokemon_t * pokemon_tire = tirerPokemon(1, database, pokemon_size);
     printf("-------\n POKEMON TIRE \n %s \n-------\n", pokemon_tire->name);
   }

   player_t * joueur = malloc(sizeof(player_t));
   joueur->niveau = 7;

   // TEST FONCTION GENERER BOUTIQUE
   //database = liste;
   pokemon_t * boutique = malloc(sizeof(pokemon_t)*5);
   pokemon_t **debut_boutique = boutique;
   boutique = genererBoutique(joueur, database, pokemon_size);
   //boutique = debut_boutique;
   //printf("\n%s\n",boutique->name);
   //boutique++;
   //printf("\n%s\n",boutique->name);
   //boutique+=sizeof(pokemon_t);
   //printf("\n%s\n",boutique->name);

   printf("\n\n------BOUTIQUE------\n\n");





   for(int i = 0; i < 5; i++)
   {

     printf("|--------------------|\n");
     printf("|                    |\n");
     printf("|     (Pokemon%d)     |\n", i+1);
     printf("|  Nom: %s           \n", boutique->name);
     printf("|  Tier: %d          \n", boutique->rarete);
     printf("|                    |\n");
     printf("|--------------------|\n");
     //printf("(POKEMON %d) : %s \n", i+1, boutique->name);
     boutique++;
   }


   // Pour une database contenant tout les tiers des pokemnons

   /*int full_database_size = 10;
   pokemon_t * full_database = malloc(sizeof(pokemon_t)*10);

   for(int i = 1; i <= 5; i++)
   {
     pokemon_t * pok = malloc(sizeof(pokemon_t));
     memcpy((*pok).name, "pokemon1 tier", 14);
     pok->rarete = i;
     full_database[i-1]=*pok;
     pokemon_t * pok2 = malloc(sizeof(pokemon_t));
     memcpy((*pok2).name, "pokemon2 tier", 14);
     pok2->rarete = i;
     full_database[(i*2)-1]=*pok2;
   }

   printf("Liste pokemons :\n");
   for(int i = 0; i < full_database_size; i++)
   {
     printf(" name : %s \n rarete : %d \n\n", full_database->name, full_database->rarete);
     full_database++;
   }*/


   /*pokemon_t * full_database;
   //pokemon_t **debut_database = full_database;
   full_database = genererationDatabase();

   affichertableau(full_database, 100);

   //int full_database_size = 20;

   //full_database = debut_database;

   // tier 1: pichu,reptincel,carapuce,abo,pikachu,roucool
   // tier 2: raichu,caninos,salameche,machoc,racaillou
   // tier 3: galopa, Tauros, mew, Noctali
   // tier 4: steelix,lugia, darkai
   // tier 5: dialga, palkia

   //printf(" name : %s \n rarete : %d \n\n", full_database[0].name, full_database[0].rarete);


   /*printf("Liste pokemons :\n");
   for(int i = 0; i < full_database_size; i++)
   {
     printf(" name : %s \n rarete : %d \n\n", full_database->name, full_database->rarete);
     full_database++;
   }*/
   /*pokemon_t * database;
   pokemon_t **debut_database = database;

   database = genererationDatabase();

   database = debut_database;

   for (int i = 0 ; i < 300 ; i++){
     printf("Pokemon numero %d\n ",i+1);
     printf("Nom : %s  ID :  %d \n",(database+i)->name,(database+i)->id);
     printf("\nAppuyez sur Entrée pour continuer...\n");
     getchar();
   }

   pokemon_t * database = genererationDatabase();

   int taille = nbPokeTier[0]*nbRepliqueTier[0];
   taille += nbPokeTier[1]*nbRepliqueTier[1];
   taille += nbPokeTier[2]*nbRepliqueTier[2];
   taille += nbPokeTier[3]*nbRepliqueTier[3];
   taille += nbPokeTier[4]*nbRepliqueTier[4];

   //affichertableau(database, taille);

   player_t * joueur = malloc(sizeof(player_t));
   joueur->niveau = 9;

   //int boutique[5];
   //genererBoutique(joueur, database, boutique);

   //int test = tirerPokemon(1, database);

   //printf("\n**%d**\n", test);

   //int boutique[5];
   pokemon_t * boutique = genererBoutique(joueur, database);


   //pokemon_t * pokemon;

   //pokemon = tirerPokemon(5,database);

   /*printf("\nname=%s tier=%d\n", pokemon->name, pokemon->rarete);


   for(int i = 0; i < 5; i++)
   {

     printf("|--------------------|\n");
     printf("|                    |\n");
     printf("|     (Pokemon%d)     |\n", i+1);
     printf("|  Nom: %s           \n", boutique[i].name);
     printf("|  Tier: %d          \n", boutique[i].rarete);
     printf("|                    |\n");
     printf("|--------------------|\n");
   }

 }
*/
