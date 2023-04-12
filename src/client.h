/**
 * @file ResClient.c
 * @author vivien (you@domain.com)
 * @brief le programme est un client réseaux, ce programme va d'abord créer un socket file descriptor. Puis il va convertir l'adresse IP du serveur en format binaire. Le programme vas ensuite ce connecté au serveur et vas recevoir les données puis la connexion ce fermera.
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "commun.h"
#include <stdbool.h>
#include <netinet/in.h>

typedef struct pokemon {
    // Définir la structure de données pour un Pokémon
    char nom[20];
    int niveau;
    int pv;
} pokemon_t;

// Fonction pour envoyer le tableau de structures au serveur
void envoyerTableau(int sockfd, pokemon_t* tableau, int tailleTableau);

// Fonction pour recevoir le tableau de structures du serveur
void recevoirTableau(int sockfd, pokemon_t* tableau, int tailleTableau);

// Fonction client
pokemon_t* client(pokemon_t* tableau, int tailleTableau);

#endif /* CLIENT_H */
