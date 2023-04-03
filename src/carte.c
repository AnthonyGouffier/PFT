#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialisation de SDL_image
    IMG_Init(IMG_INIT_PNG);

    // Initialisation de SDL_ttf
    TTF_Init();

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 250, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Chargement de l'image
    SDL_Surface* imageSurface = IMG_Load("ressources/img/image.jpg");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    // Chargement de la police
    TTF_Font* font = TTF_OpenFont("arial.ttf", 16);
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Images Prix", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Dessin du rectangle rouge
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect redRect = {0, 0, 320, 250};
    SDL_RenderFillRect(renderer, &redRect);

    // Dessin du rectangle noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect blackRect = {10, 10, 300, 230};
    SDL_RenderFillRect(renderer, &blackRect);

    // Affichage des l'image
    SDL_Rect imageRect = {10, 10, 300, 210};
    SDL_RenderCopy(renderer, imageTexture, NULL,&imageRect);

    // Affichage du texte
    int textW = textSurface->w;
    int textH = textSurface->h;
    int textX = (320 - textW) / 2;
    int textY = (250 - textH) - 10;
    SDL_Rect textRect = {textX,textY,textW,textH};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);

    // Attente de l'utilisateur
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Libération des ressources
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}