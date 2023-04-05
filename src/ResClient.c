#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "commun.h"

#define PORT 8080



int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    my_struct data;

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

    // boucle pour envoyer des données au serveur en continu
    for(int i=0;i<1;i++) {
        // saisie des données à envoyer
        printf("Entrez un entier : ");
        scanf("%d", &(data.i));
        printf("Entrez un caractère : ");
        scanf(" %c", &(data.c));

        // envoi des données au serveur
        if (send(sock, &data, sizeof(data), 0) == -1) {
            perror("Erreur lors de l'envoi");
            exit(EXIT_FAILURE);
        }

        printf("Données envoyées avec succès.\n");
    }

    // fermer la connexion
    close(sock);

    return 0;
}
