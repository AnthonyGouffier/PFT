#include "commun.h"
#include "carte.h"


/*******************************************GENERATION*******************************************************/

carteBoutique genererCartePkmBoutique(pokemon_t pokemon,SDL_Renderer* renderer, SDL_Window * window ,int x , int y) {
    // Récupération de la rareté du pokémon
    carteBoutique carte; 
    int pokemonRarity = pokemon.rarete;

    // Dessin du rectangle avec la couleur spécifiée
    carte.lvlRect.x=x; 
    carte.lvlRect.y=y;
    carte.lvlRect.w=320;
    carte.lvlRect.h=250;
    
    // Calcul des coordonnées du coin supérieur gauche du rectangle noir
    int blackRectX = (carte.lvlRect.w - 300) / 2;
    int blackRectY = (carte.lvlRect.h - 230) / 2;
    
    carte.blackRect.x=blackRectX;
    carte.blackRect.y=blackRectY;
    carte.blackRect.w=300;
    carte.blackRect.h = 230;
    
    // Calcul de la hauteur du rectangle bleu
    int blueRectH = carte.blackRect.h * 0.75;

    carte.blueRect.x = blackRectX;
    carte.blueRect.y = blackRectY;
    carte.blueRect.w = carte.blackRect.w;
    carte.blueRect.h = blueRectH;
    
    // Chargement de l'image de fond
    SDL_Surface* bgSurface = IMG_Load("ressources/img/backgroundcard.jpg");
    carte.bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    
    // Chargement de l'image du Pokémon
    SDL_Surface* pkmSurface = pokemon.imgSurface;
    carte.pkmTexture = SDL_CreateTextureFromSurface(renderer, pkmSurface);
    
    // Récupération des dimensions de l'image
    int imageWidth = pkmSurface->w;
    int imageHeight = pkmSurface->h;
    
    // Calcul des dimensions du rectangle de destination
    int destWidth = carte.blueRect.w;
    int destHeight = (float)imageHeight / (float)imageWidth * destWidth;
    
    // Si le rectangle de destination est trop grand pour la zone disponible,
    // ajustez sa hauteur et recalculez sa largeur en conséquence
    if (destHeight > carte.blueRect.h) {
        destHeight = carte.blueRect.h;
        destWidth = (float)imageWidth / (float)imageHeight * destHeight;
    }
    
    // Calcul des coordonnées du coin supérieur gauche du rectangle de destination
    int destX = carte.blueRect.x + (carte.blueRect.w - destWidth) / 2;
    int destY = carte.blueRect.y + (carte.blueRect.h - destHeight) / 2;
    
    // Définition du rectangle de destination
    carte.destRect.x = destX ; 
    carte.destRect.y =destY ;
    carte.destRect.w =destWidth;
    carte.destRect.h =destHeight;

    // Chargement de la police Arial
    TTF_Font* font = TTF_OpenFont("ressources/font/spiegel.ttf",22);
    if (!font) {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }
    
    // Création d'une surface contenant le texte rendu avec la police Arial
    SDL_Color textColor = {255,255,255};
    
    char* cout = int_to_string(pokemon.rarete);
    SDL_Surface* prixText = TTF_RenderText_Solid(font,cout,textColor);
    if (!prixText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
    }
    
    // Création d'une texture à partir de la surface de texte
    carte.prixTexture = SDL_CreateTextureFromSurface(renderer,prixText);
    if (!carte.prixTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
    }
    
    // Affichage du texte dans la partie noire restante du rectangle noir
    int prixtextW = prixText->w;
    int prixtextH = prixText->h;
    int prixtextX = blackRectX + (carte.blackRect.w * 0.80) - (prixtextW / 2);
    int prixtextY = blackRectY + blueRectH + (carte.blackRect.h - blueRectH - prixtextH) / 2;
    carte.prixRect.x=prixtextX;
    carte.prixRect.y=prixtextY;
    carte.prixRect.w=prixtextW;
    carte.prixRect.h=prixtextH;
    SDL_Surface* nomText = TTF_RenderText_Solid(font,pokemon.name,textColor);
    if (!nomText) {
        printf("Erreur de rendu du texte: %s\n", TTF_GetError());
    }
    
    // Création d'une texture à partir de la surface de texte
    carte.nomTexture = SDL_CreateTextureFromSurface(renderer,nomText);
    if (!carte.nomTexture) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
    }
    // Affichage du texte dans la partie noire restante du rectangle noir
    int nomtextW = nomText->w;
    int nomtextH = nomText->h;
    int nomtextX = blackRectX + (carte.blackRect.w * 0.50) - (nomtextW / 2);
    int nomtextY = blackRectY + blueRectH + (carte.blackRect.h - blueRectH - nomtextH) / 2;
    carte.nomRect.x=nomtextX;
    carte.nomRect.y=nomtextY;
    carte.nomRect.w=nomtextW;
    carte.nomRect.h=nomtextH;
    
    // Dessin du rectangle vert à droite du texte "Prix"
    SDL_Surface* pieceSurface = IMG_Load("ressources/img/piece.png");
    carte.pieceTexture = SDL_CreateTextureFromSurface(renderer, pieceSurface);
    int rectanglePieceX = prixtextX + prixtextW;
    int rectanglePieceY = prixtextY;
    carte.rectanglePiece.x=rectanglePieceX;
    carte.rectanglePiece.y=rectanglePieceY;
    carte.rectanglePiece.w=25;
    carte.rectanglePiece.h=25;
    return carte;
}
/*************************************AFFICHAGE*************************************/
void afficherCartePkmBoutique(carteBoutique carte,SDL_Renderer* renderer,pokemon_t pokemon){
    // Définition de la couleur de dessin en fonction de la rareté du pokémon
    switch (pokemon.rarete) {
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
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Doré
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
    }

    SDL_RenderFillRect(renderer,&carte.lvlRect);
    // Dessin du rectangle noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &carte.blackRect);
    
    // Dessin du rectangle bleu
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer,&carte.blueRect);
    
    SDL_RenderCopy(renderer, carte.bgTexture, NULL,&carte.blueRect);
    // Affichage de l'image dans le rectangle de destination
    SDL_RenderCopy(renderer, carte.pkmTexture, NULL, &carte.destRect);
    SDL_RenderCopy(renderer,carte.prixTexture,NULL,&carte.prixRect);
    SDL_RenderCopy(renderer,carte.nomTexture,NULL,&carte.nomRect);
    SDL_RenderCopy(renderer, carte.pieceTexture, NULL,&carte.rectanglePiece);
}