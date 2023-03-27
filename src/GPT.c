#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    /*METTRE LES PARAMS A INIATILISER POUR LA SDL*/
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

    SDL_Window* fenetre = SDL_CreateWindow("Ma fenêtre SDL",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            640, 480,
                                            SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 480, 32,
                                                0x00FF0000,
                                                0x0000FF00,
                                                0x000000FF,
                                                0xFF000000);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

    if (surface == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Rect position = { 0, 0, 0, 0 };
    SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(fenetre), &position);
    SDL_UpdateWindowSurface(fenetre);

    SDL_Event evenement;
    int continuer = 1;

    while (continuer) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                continuer = 0;
            }
        }
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(fenetre);
    
    SDL_Quit();

    return 0;
}
