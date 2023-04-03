#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

int initialiserModules() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Erreur d'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
}

int main(int argc, char* argv[]) {
    initialiserModules();    
    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 250, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Dessin du rectangle rouge
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect redRect = {0, 0, 320, 250};
    SDL_RenderFillRect(renderer, &redRect);

    // Calcul des coordonnées du coin supérieur gauche du rectangle noir
    int blackRectX = (redRect.w - 300) / 2;
    int blackRectY = (redRect.h - 230) / 2;

    // Dessin du rectangle noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect blackRect = {blackRectX, blackRectY, 300, 230};
    SDL_RenderFillRect(renderer, &blackRect);

    // Calcul de la hauteur du rectangle bleu
    int blueRectH = blackRect.h * 0.75;

    // Dessin du rectangle bleu
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect blueRect = {blackRectX, blackRectY, blackRect.w, blueRectH};
    SDL_RenderFillRect(renderer,&blueRect);
    // Chargement de l'image
    SDL_Surface* imageSurface = IMG_Load("ressources/img/image.jpg");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_RenderCopy(renderer, imageTexture, NULL,&blueRect);
    
    
    
    // Chargement de la police Arial
    TTF_Font* font = TTF_OpenFont("ressources/font/spiegel.ttf",22);
    if (!font) {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }

    // Création d'une surface contenant le texte rendu avec la police Arial
    SDL_Color textColor = {255,255,255};

    SDL_Surface* prixText = TTF_RenderText_Solid(font,"Prix",textColor);
    if (!prixText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
    }

    // Création d'une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer,prixText);
    if (!textTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
    }

    // Affichage du texte dans la partie noire restante du rectangle noir
    int prixtextW = prixText->w;
    int prixtextH = prixText->h;
    int prixtextX = blackRectX + (blackRect.w * 0.80) - (prixtextW / 2);
    int prixtextY = blackRectY + blueRectH + (blackRect.h - blueRectH - prixtextH) / 2;
    SDL_Rect prixRect = {prixtextX,prixtextY,prixtextW,prixtextH};
    SDL_RenderCopy(renderer,textTexture,NULL,&prixRect);

    SDL_Surface* nomText = TTF_RenderText_Solid(font,"Nom",textColor);
    if (!nomText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
    }

    // Création d'une texture à partir de la surface de texte
    textTexture = SDL_CreateTextureFromSurface(renderer,nomText);
    if (!textTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
    }
    // Affichage du texte dans la partie noire restante du rectangle noir
    int nomtextW = nomText->w;
    int nomtextH = nomText->h;
    int nomtextX = blackRectX + (blackRect.w * 0.10) - (nomtextW / 2);
    int nomtextY = blackRectY + blueRectH + (blackRect.h - blueRectH - nomtextH) / 2;
    SDL_Rect nomRect = {nomtextX,nomtextY,nomtextW,nomtextH};
    SDL_RenderCopy(renderer,textTexture,NULL,&nomRect);

    // Dessin du rectangle vert à droite du texte "Prix"
    imageSurface = IMG_Load("ressources/img/piece.png");
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    int rectanglePieceX = prixtextX + prixtextW;
    int rectanglePieceY = prixtextY;
    SDL_Rect rectanglePiece = {rectanglePieceX, rectanglePieceY, 25, 25};
    SDL_RenderCopy(renderer, imageTexture, NULL,&rectanglePiece);


    // Attente de l'utilisateur
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    // Mise à jour de l'écran
    SDL_RenderPresent(renderer);
    }


    // Libération des ressources

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}