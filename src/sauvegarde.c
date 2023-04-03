#include "entites.h"

#define N 7
#define TAILLE 9


void sauvegardeEquipe(pokemon_t matrice[N][N],player_t joueur){
    pokemon_t *savePKM[TAILLE];

    // Allocation dynamique de chaque pokemon_t et stockage de l'adresse dans le tableau de pointeurs
    for (int i = 0; i < TAILLE; i++) {
        savePKM[i] = malloc(sizeof(pokemon_t));
        // Initialisation des champs du pokemon_t
    }
    int cpt=0;
    for (int i = 0 ; i < N ; i++){
        for (int j = 0; j < N;j++){
            if (matrice[i][j].alive==1){
                savePKM[cpt]=&matrice[i][j];
                cpt++;
            }
        }
    }
    return savePKM;
}

void Suppsauvegarde(pokemon_t *savePKM[]){
    // Libération de la mémoire allouée pour chaque pokemon_t
    for (int i = 0; i < TAILLE; i++) {
        free(savePKM[i]);
    }
    return 0;
    printf("Sauvegarde Effectuee :) ");
}
