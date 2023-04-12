/**
 * @file ResServer.c
 * @author vivien (you@domain.com)
 * @brief Le programme est un serveur pour le réseaux. Ce programme vas d'abord créer une socket puis vas ensuite configurer l'adresse IP et le port du serveur. Une fois cela fais il vas attaché le socket à l'adresse IP et au port. Le serveur vas ensuite attendre une connexion. Une fois la connexion faite le serveur vas envoyer les données au client et fermera la connexion.
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
// Fichier serveur.c

#include "commun.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>


// Tableau de structures pour le client 1
struct Joueur *tableauClient1;
int tailleTableauClient1 = 0;

// Tableau de structures pour le client 2
struct Joueur *tableauClient2;
int tailleTableauClient2 = 0;

// Fonction pour gérer la connexion avec un client
void *gestionClient(void *socketClientPtr) {
    int clientSocket = *((int *)socketClientPtr);
    free(socketClientPtr);

    // Recevoir l'ID du client
    int clientId;
    if (recv(clientSocket, &clientId, sizeof(int), 0) == -1) {
        perror("Erreur lors de la réception de l'ID du client");
        close(clientSocket);
        return NULL;
    }

    // Recevoir la taille du tableau de structures du client
    int tailleTableau;
    if (recv(clientSocket, &tailleTableau, sizeof(int), 0) == -1) {
        perror("Erreur lors de la réception de la taille du tableau de structures du client");
        close(clientSocket);
        return NULL;
    }

    // Recevoir le tableau de structures du client
    struct Joueur *tableauClient;
    if (clientId == 1) {
        tableauClient = realloc(tableauClient1, tailleTableau * sizeof(struct Joueur));
        if (tableauClient == NULL) {
            perror("Erreur lors de la réallocation du tableau pour le client 1");
            close(clientSocket);
            return NULL;
        }
        tableauClient1 = tableauClient;
        tailleTableauClient1 = tailleTableau;
    } else if (clientId == 2) {
        tableauClient = realloc(tableauClient2, tailleTableau * sizeof(struct Joueur));
        if (tableauClient == NULL) {
            perror("Erreur lors de la réallocation du tableau pour le client 2");
            close(clientSocket);
            return NULL;
        }
        tableauClient2 = tableauClient;
        tailleTableauClient2 = tailleTableau;
    } else {
        printf("ID du client invalide : %d\n", clientId);
        close(clientSocket);
        return NULL;
    }

    if (recv(clientSocket, tableauClient, tailleTableau * sizeof(struct Joueur), 0) == -1) {
        perror("Erreur lors de la réception du tableau de structures du client");
        close(clientSocket);
        return NULL;
    }

    // Envoyer la taille du tableau de structures au client correspondant
    if (clientId == 1) {
        if (send(clientSocket, &tailleTableauClient1, sizeof(int), 0) == -1) {
            perror("Erreur lors de l'envoi de la taille du tableau de structures au client 1");
            close(clientSocket);
            return NULL;
        }
    } else if (clientId == 2) {
        if (send(clientSocket, &tailleTableauClient2, sizeof(int), 0) == -1) {
            perror("Erreur lors de l'envoi de la taille du tableau de structures au client 2");
            close(clientSocket);
            return NULL;
        }
    }

    // Fermer la connexion avec le client
    close(clientSocket);

    // Libérer la mémoire allouée pour le tableau
    free(tableauClient);

    return NULL;
}