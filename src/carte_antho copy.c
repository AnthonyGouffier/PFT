#include "commun.h"



void creerBouton(pokemon_t pokemon) {
    initialiserModules();   
    // Récupération de l'ID du pokémon
    printf("%d",pokemon.id);

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 250, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Récupération de la rareté du pokémon
    int pokemonRarity = pokemon.rarete;

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
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Doré
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
}

// Dessin du rectangle avec la couleur spécifiée
    SDL_Rect redRect = {0, 0, 320, 250};
    SDL_RenderFillRect(renderer,&redRect);

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
    SDL_Surface* imageSurface = IMG_Load("ressources/img/backgroundcard.jpg");
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_RenderCopy(renderer, imageTexture, NULL,&blueRect);
    // Construction du nom de fichier de l'image
    char filename[64];
    sprintf(filename, "ressources/img/Artwork2D/%d.png", pokemon.id);

    printf("Localisation : %s",filename);
    // Chargement de l'image
    imageSurface = IMG_Load(filename);
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    // Récupération des dimensions de l'image
    int imageWidth = imageSurface->w;
    int imageHeight = imageSurface->h;

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

    // Affichage de l'image dans le rectangle de destination
    SDL_RenderCopy(renderer, imageTexture, NULL, &destRect);
    
    
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

    
    SDL_Surface* nomText = TTF_RenderText_Solid(font,pokemon.name,textColor);
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
    int nomtextX = blackRectX + (blackRect.w * 0.50) - (nomtextW / 2);
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