#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int arc,char* argv[]) {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Mon application SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image
    SDL_Surface* imageSurface = IMG_Load("./ressources/img/image.jpg");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    // Initialisation du bouton
    SDL_Rect buttonRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 50 };

    // Boucle principale
    SDL_Event event;
    bool quit = false;
    bool imageVisible = true;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && SDL_PointInRect(&(SDL_Point){ event.button.x, event.button.y }, &buttonRect)) {
                        imageVisible = false;
                    }
                    break;
            }
        }

        // Affichage de l'image et du bouton
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (imageVisible) {
            printf("Le bouton n'est pas clique\n");
            SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &buttonRect);

        SDL_RenderPresent(renderer);
    }

    // Libération de la mémoire
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
