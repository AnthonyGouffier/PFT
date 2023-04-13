/**
 * \file combats.h
 * @author mael 
 * @brief le combat 
 * @version 0.1
 * @date 2023-04-03
 * 
 * 
 */
#ifndef COMBATS_H
#define COMBATS_H

#include "commun.h"
#include "entites.h"

#define pok 1
#define enemi 2
#define N 6

typedef struct PL_s{
  int hp;
  int level;
}PL_t;







/**
 * @brief verifi si dans la matrice
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int valides(int x,int y);

/**
 * @brief calcule les degat a infliger a un pokemon
 * 
 * @param hp 
 * @param armor 
 * @param attaque 
 * @return int 
 */
int degats_subi_pkm(int hp,int armor,int attaque);

/**
 * @brief si il est mort 
 * 
 * @param hp 
 * @return int 
 */
int est_mort_pkm(int hp);

/**
 * @brief verifi si il a la porter renvoi 1 sinon 0
 * 
 * @param mat 
 * @param porter 
 * @param xpos 
 * @param ypos 
 * @return int 
 */
int aporter(pokemon_t * mat[N][N],int porter,int xpos,int ypos);



/**
 * @brief efface un pokemon en mettan toute les stat a 0
 * 
 * @param mat 
 * @param pos 
 */
void effacer(pokemon_t * mat[N][N],pos_t pos);


/**
 * @brief deplace un pokemon d une case a une case
 * 
 * @param mat 
 * @param pos 
 * @param newpos 
 */
void deplacement_pok(pokemon_t * mat[N][N],pos_t pos,pos_t newpos);


/**
 * @brief avance un pokemon ver un enemie de 1
 * 
 * @param mat 
 * @param xenemie 
 * @param yenemie 
 * @param posx 
 * @param posy 
 * @return pos_t 
 */
pos_t avance(pokemon_t * mat[N][N],int xenemie,int yenemie,int posx,int posy);

/**
 * @brief detecte le premiere enemie le plus proche et renvoi ces cordone
 * 
 * @param pos 
 * @param mat 
 * @param equipe 
 * @return pos_t 
 */
pos_t detecte_enemie_proche(pokemon_t * mat[N][N],pos_t pos,int equipe);


/**
 * @brief degats infliger a un joueur 
 * 
 * @param mat 
 * @param stage 
 * @param hp 
 * @return int 
 */
int dmg_player(pokemon_t * mat[N][N],int stage,int hp,int equipe);

/**
 * @brief recupere et retoune les hp d un pokemon a des cordonner donner
 * 
 * @param mat 
 * @param x 
 * @param y 
 * @return int 
 */
int recuperehp(pokemon_t * mat[N][N],int x,int y);

/**
 * @brief affiche le test (beta)
 * 
 * @param automate 
 */
void affiche_test(pokemon_t * automate[N][N]);




/**
 * @brief affiche les stat d un pokemon a des cordonner donner
 * 
 * @param mat 
 * @param pos 
 */
void affiche_stat(pokemon_t * mat[N][N],pos_t pos);

/**
 * @brief donne tout les stat des pokemon de la matrice 
 * 
 * @param mat 
 */
void affiche_tout(pokemon_t * mat[N][N]);

/**
 * @brief fait un tour de combats
 * 
 * @param mat 
 * @param tour 
 */
void combats(pokemon_t * mat[N][N],int tour);

#endif