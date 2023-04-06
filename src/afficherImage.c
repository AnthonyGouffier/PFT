/**
 * @file afficherImage.c
 * @author Gouffier Anthony
 * @brief test de la SDL 
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialisation de SDL_image
    IMG_Init(IMG_INIT_JPG);

    // Chargement de l'image
    SDL_Surface* imageSurface = IMG_Load("ressources/img/image.jpg");
    if (!imageSurface) {
        printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
        return 1;
    }

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Affichage de l'image sur le renderer
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Attente de l'utilisateur
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Libération des ressources
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}


