#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "commun.h"

#define PORT 8080

int read_data_from_network(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    my_struct data;

    // création d'un socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // configuration de l'adresse IP et du numéro de port du serveur
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // modification de l'adresse IP ici
    address.sin_port = htons(PORT);

    // attachement du socket à l'adresse IP et au numéro de port du serveur
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erreur lors de l'attachement du socket à l'adresse IP et au numéro de port du serveur");
        exit(EXIT_FAILURE);
    }

    // mise en attente de connexions entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Erreur lors de la mise en attente de connexions entrantes");
        exit(EXIT_FAILURE);
    }

    printf("Le serveur est prêt à recevoir des données...\n");

    // boucle pour recevoir des données en continu
    for(int i=0;i<1;i++) {
        // acceptation de la connexion entrante
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Erreur lors de l'acceptation de la connexion entrante");
            exit(EXIT_FAILURE);
        }

        // réception des données envoyées par le client
        if (recv(new_socket, &data, sizeof(data), 0) == -1) {
            perror("Erreur lors de la réception des données");
            exit(EXIT_FAILURE);
        }

        // affichage des données reçues
        printf("Entier reçu : %d\n", data.i);
        printf("Caractère reçu : %c\n", data.c);

        // envoi d'une réponse au client
        char *msg = "Données reçues avec succès.";
        if (send(new_socket, msg, strlen(msg), 0) == -1) {
            perror("Erreur lors de l'envoi de la réponse");
            exit(EXIT_FAILURE);
        }

        // fermeture de la connexion avec le client
        close(new_socket);
    }

    return 0;
}
