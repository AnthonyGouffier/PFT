/**
 * @file generer_carteV1.c
 * @author Gouffier Anthony
 * @brief programme qui affiche la carte du pokemon
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commun.h"

void generer_carteV1(pokemon_t* pokemon, SDL_Renderer* renderer, int x, int y) {
    // Récupération de la rareté du pokémon
    int pokemonRarity = pokemon->rarete;

    // Dessin du rectangle avec la couleur spécifiée
    SDL_Rect redRect = {x, y, 320, 250};

    // Calcul des coordonnées du coin supérieur gauche du rectangle noir
    int blackRectX = x + (redRect.w - 300) / 2;
    int blackRectY = y + (redRect.h - 230) / 2;

    SDL_Rect blackRect = {blackRectX, blackRectY, 300, 230};

    // Calcul de la hauteur du rectangle bleu
    int blueRectH = blackRect.h * 0.75;

    SDL_Rect blueRect = {blackRectX, blackRectY, blackRect.w, blueRectH};

    // Chargement de l'image de fond
    SDL_Surface* bgSurface = IMG_Load("ressources/img/backgroundcard.jpg");
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);

    // Chargement de l'image du Pokémon
    SDL_Surface* pkmSurface = pokemon->imgSurface;
    SDL_Texture* pkmTexture = SDL_CreateTextureFromSurface(renderer, pkmSurface);

    // Récupération des dimensions de l'image
    int imageWidth = pkmSurface->w;
    int imageHeight = pkmSurface->h;

    // Calcul des dimensions du rectangle de destination
    int destWidth = blueRect.w;
    int destHeight = (float)imageHeight / (float)imageWidth * destWidth;

    // Si le rectangle de destination est trop grand pour la zone disponible,
    // ajustez sa hauteur et recalculez sa largeur en conséquence
    if (destHeight > blueRect.h) {
        destHeight = blueRect.h;
        destWidth = (float)imageWidth / (float)imageHeight * destHeight;
    }

    // Calcul des coordonnées du coin supérieur gauche du rectangle de destination
    int destX = blueRect.x + (blueRect.w - destWidth) / 2;
    int destY = blueRect.y + (blueRect.h - destHeight) / 2;

    // Définition du rectangle de destination
    SDL_Rect destRect = {destX, destY, destWidth, destHeight};

    // Chargement de la police Arial
    TTF_Font* font = TTF_OpenFont("ressources/font/spiegel.ttf",22);
    if (!font) {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }

    // Création d'une surface contenant le texte rendu avec la police Arial
    SDL_Color textColor = {255,255,255};

    char* cout = int_to_string(pokemon->rarete);
    SDL_Surface* prixText = TTF_RenderText_Solid(font,cout,textColor);
    if (!prixText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }
    // Création d'une texture à partir de la surface de texte
    SDL_Texture* prixTexture = SDL_CreateTextureFromSurface(renderer,prixText);
    if (!prixTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
        // Gestion de l'erreur
    }

    // Affichage du texte dans la partie noire restante du rectangle noir
    int prixtextW = prixText->w;
    int prixtextH = prixText->h;
    int prixtextX = blackRectX + (blackRect.w * 0.80) - (prixtextW / 2);
    int prixtextY = blackRectY + blueRectH + (blackRect.h - blueRectH - prixtextH) / 2;
    SDL_Rect prixRect = {prixtextX,prixtextY,prixtextW,prixtextH};

    SDL_Surface* nomText = TTF_RenderText_Solid(font,pokemon->name,textColor);
    if (!nomText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }

    // Création d'une texture à partir de la surface de texte
    SDL_Texture* nomTexture = SDL_CreateTextureFromSurface(renderer,nomText);
    if (!nomTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
        // Gestion de l'erreur
    }
    // Affichage du texte dans la partie noire restante du rectangle noir
    int nomtextW = nomText->w;
    int nomtextH = nomText->h;
    int nomtextX = blackRectX + (blackRect.w * 0.50) - (nomtextW / 2);
    int nomtextY = blackRectY + blueRectH + (blackRect.h - blueRectH - nomtextH) / 2;
    SDL_Rect nomRect = {nomtextX,nomtextY,nomtextW,nomtextH};

    // Dessin du rectangle vert à droite du texte "Prix"
    SDL_Surface* pieceSurface = IMG_Load("ressources/img/piece.png");
    SDL_Texture* pieceTexture = SDL_CreateTextureFromSurface(renderer, pieceSurface);
        int rectanglePieceX = prixtextX + prixtextW;
        int rectanglePieceY = prixtextY;
        SDL_Rect rectanglePiece = {rectanglePieceX, rectanglePieceY, 25, 25};

        // Définition de la couleur de dessin en fonction de la rareté du pokémon
        switch (pokemonRarity) {
            case 1:
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Gris
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // Violet
                break;
            case 5:
                SDL_SetRenderDrawColor(renderer, 255, 215, 50, 255); // Doré
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
        }

        SDL_RenderFillRect(renderer,&redRect);
        // Dessin du rectangle noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &blackRect);

        // Dessin du rectangle bleu
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer,&blueRect);

        SDL_RenderCopy(renderer, bgTexture, NULL,&blueRect);
        // Affichage de l'image dans le rectangle de destination
        SDL_RenderCopy(renderer, pkmTexture, NULL, &destRect);
        SDL_RenderCopy(renderer,prixTexture,NULL,&prixRect);
        SDL_RenderCopy(renderer,nomTexture,NULL,&nomRect);
        SDL_RenderCopy(renderer, pieceTexture, NULL,&rectanglePiece);

    SDL_FreeSurface(bgSurface);
    SDL_DestroyTexture(bgTexture);
    SDL_FreeSurface(pkmSurface);
    SDL_DestroyTexture(pkmTexture);
    SDL_FreeSurface(prixText);
    SDL_DestroyTexture(prixTexture);
    SDL_FreeSurface(nomText);
    SDL_DestroyTexture(nomTexture);
}