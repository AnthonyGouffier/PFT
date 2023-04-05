#include "commun.h"

int main(int argc, char* argv[]) {
    initialiserModules();
    pokemon_t* pokemon = createPkmDatabase(1);

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 250, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1 ,0);

    // Attente de l'utilisateur
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
        // Mise à jour de l'écran
        generer_carteV1(pokemon, renderer, 0 ,0);
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}