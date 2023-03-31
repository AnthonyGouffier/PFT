#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {
    // Initialisation de la SDL, SDL_image 
    // Création de la fenêtre et du renderer

    // Chargement des images et des polices
    // Création des textures

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            // Gestion des événements (clics, clavier, etc.)
            // Si l'utilisateur ferme la fenêtre, quit = 1
        }

        // Effacer l'écran
        SDL_RenderClear(renderer);

        // Dessiner les éléments de l'interface
        // Utilisez SDL_RenderCopy et SDL_RenderFillRect

        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources et fermeture de la SDL
    return 0;
}