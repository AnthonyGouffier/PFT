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

// Fichier client.c

#include "commun.h"
#include <stdbool.h>
#include <netinet/in.h>
#include "entite.h"
#include "client.h" // Inclure le fichier d'en-tête du client

// Fonction pour envoyer le tableau de structures au serveur
void envoyerTableau(int sockfd, pokemon_t* tableau, int tailleTableau) {
    
    // Envoyer l'ID du joueur au serveur
    int bytesSent = send(sockfd, &(joueur->id), sizeof(int), 0);
    if (bytesSent == -1) {
        perror("Erreur d'envoi de l'ID du joueur");
        exit(EXIT_FAILURE);
    }

    // Envoyer la taille du tableau au serveur d'abord
    int bytesSent = send(sockfd, &tailleTableau, sizeof(int), 0);
    if (bytesSent == -1) {
        perror("Erreur d'envoi de la taille du tableau");
        exit(EXIT_FAILURE);
    }

    // Envoyer ensuite le tableau de structures
    bytesSent = send(sockfd, tableau, tailleTableau * sizeof(pokemon_t), 0);
    if (bytesSent == -1) {
        perror("Erreur d'envoi du tableau de structures");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour recevoir le tableau de structures du serveur
void recevoirTableau(int sockfd, pokemon_t* tableau, int tailleTableau) {
    // Recevoir la taille du tableau du serveur d'abord
    int bytesRead = recv(sockfd, &tailleTableau, sizeof(int), 0);
    if (bytesRead == -1) {
        perror("Erreur de réception de la taille du tableau");
        exit(EXIT_FAILURE);
    }

    // Recevoir ensuite le tableau de structures
    bytesRead = recv(sockfd, tableau, tailleTableau * sizeof(pokemon_t), 0);
    if (bytesRead == -1) {
        perror("Erreur de réception du tableau de structures");
        exit(EXIT_FAILURE);
    }
}

// Fonction client
pokemon_t* client(pokemon_t* tableau, int tailleTableau) {
    // Paramètres de connexion
    char* serverIP = "127.0.0.1"; // Adresse IP du serveur
    int serverPort = 8080; // Port du serveur

    // Créer une socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Erreur de création de la socket");
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse du serveur
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);

    // Se connecter au serveur
    int connResult = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (connResult == -1) {
        perror("Erreur de connexion au serveur");
        exit(EXIT_FAILURE);
    }

    // Envoyer le tableau de structures au serveur
    envoyerTableau(sockfd, tableau, tailleTableau);

    // Recevoir le tableau de structures du serveur
    recevoirTableau(sockfd, tableau, tailleTableau);

    // Fermer la socket
    close(sockfd);

    // Retourner le tableau reçu du serveur
    return tableau;
}
