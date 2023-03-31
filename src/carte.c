#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Cadre avec Image et Texte";

const int FRAME_WIDTH = 20;
const SDL_Color FRAME_COLOR = { 102, 0, 102, 0 };

const int TEXT_PADDING = 10;
const char* TEXT_LEFT = "poke";
const char* TEXT_RIGHT = "niv";

int main(int argc, char* args[]) {
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("./ressources/img/image.jpg");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Chargement de la police de caractères
    TTF_Font* font = TTF_OpenFont("./ressources/font/arial.ttf", 16);
    if (font == NULL) {
        printf("Erreur de chargement de la police de caractères : %s\n", TTF_GetError());
        return 1;
    }

    // Création de la texture pour le texte à gauche
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface* textSurfaceLeft = TTF_RenderText_Solid(font, TEXT_LEFT, textColor);
    SDL_Texture* textTextureLeft = SDL_CreateTextureFromSurface(renderer, textSurfaceLeft);
    SDL_Rect textRectLeft = { FRAME_WIDTH + TEXT_PADDING, WINDOW_HEIGHT - FRAME_WIDTH - textSurfaceLeft->h - TEXT_PADDING, textSurfaceLeft->w, textSurfaceLeft->h };
    SDL_FreeSurface(textSurfaceLeft);

    // Création de la texture pour le texte à droite
    SDL_Surface* textSurfaceRight = TTF_RenderText_Solid(font, TEXT_RIGHT, textColor);
    SDL_Texture* textTextureRight = SDL_CreateTextureFromSurface(renderer, textSurfaceRight);
    SDL_Rect textRectRight = { WINDOW_WIDTH - FRAME_WIDTH - TEXT_PADDING - textSurfaceRight->w, WINDOW_HEIGHT - FRAME_WIDTH - textSurfaceRight->h - TEXT_PADDING, textSurfaceRight->w, textSurfaceRight->h };
    SDL_FreeSurface(textSurfaceRight);
    // Boucle principale
int quit = 0;
SDL_Event e;
while (!quit) {
    // Gestion des événements
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
    }

    // Effacement de l'écran
    SDL_RenderClear(renderer);

    // Affichage de l'image de fond
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Dessin du cadre
    SDL_SetRenderDrawColor(renderer, FRAME_COLOR.r, FRAME_COLOR.g, FRAME_COLOR.b, FRAME_COLOR.a);
    SDL_Rect frameRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    for (int i = 0; i < FRAME_WIDTH; i++) {
        SDL_RenderDrawRect(renderer, &frameRect);
        frameRect.x++;
        frameRect.y++;
        frameRect.w -= 2;
        frameRect.h -= 2;
    }

    // Affichage du texte à gauche
    SDL_RenderCopy(renderer, textTextureLeft, NULL, &textRectLeft);

    // Affichage du texte à droite
    SDL_RenderCopy(renderer, textTextureRight, NULL, &textRectRight);

    // Affichage à l'écran
    SDL_RenderPresent(renderer);
}

// Libération de la mémoire et fermeture de la SDL
SDL_DestroyTexture(backgroundTexture);
SDL_DestroyTexture(textTextureLeft);
SDL_DestroyTexture(textTextureRight);
TTF_CloseFont(font);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
TTF_Quit();
SDL_Quit();

return 0;
}
