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


#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "commun.h"

#define PORT 8080

int main(int argc, char const *argv[]) {

    int sock = 0;
    struct sockaddr_in serv_addr;
    pokemon_t pokemon[2];

    // création d'un socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Erreur lors de la création du socket \n");
        return -1;
    }

    // conversion de l'adresse IP du serveur au format binaire
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n Adresse invalide/Adresse non prise en charge \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connexion au serveur échouée \n");
        return -1;
    }

    // réception de l'équipe de pokemons envoyée par le serveur
    if (recv(sock, &pokemon, sizeof(pokemon), 0) == -1) {
        perror("Erreur lors de la réception de l'équipe de pokemons");
        exit(EXIT_FAILURE);
    }

    printf("Equipe de pokemons reçue :\n");
    printPkm(pokemon[1]);
    afficherEquipe(pokemon, 2);

    // fermer la connexion
    close(sock);

    return 0;
}
