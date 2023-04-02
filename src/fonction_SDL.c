#include "commun.h"
#include <SDL.h>
/*
CE FICHIER CONTIENT DES FONCTION POUR UTILISER LA SDL PLUS RAPIDEMENT
*/


/*
paramètres  SDL_Renderer, coordonnées x et y du rectangle contenant les cases
largeur et sa hauteur width et height,
nombre de lignes et de colonnes de cases rows et cols
*/
void drawCases(SDL_Renderer *renderer, int x, int y, int width, int height, int rows, int cols)
{
    // Dessiner le rectangle
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Dessiner les cases
    int caseWidth = width / cols;
    int caseHeight = height / rows;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int caseX = x + j * caseWidth;
            int caseY = y + i * caseHeight;

            // Dessiner la bordure de la case
            SDL_Rect caseRect = {caseX + 1, caseY + 1, caseWidth - 2, caseHeight - 2};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &caseRect);

            // Dessiner l'illusion de perspective
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderDrawLine(renderer, caseX + caseWidth - 1 , caseY + caseHeight - caseHeight /4 -1 , caseX + caseWidth - caseWidth /4 -1 , caseY + caseHeight -1 );
            SDL_RenderDrawLine(renderer ,caseX + caseWidth - caseWidth /4 -1 , caseY + caseHeight -1 ,caseX + caseWidth /4 ,caseY + caseHeight -1 );
        }
    }
}



void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}



void SDLcheck(){
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d !\n",nb.major,nb.minor,nb.patch);
    exit(EXIT_FAILURE);
}

void gestionQuitter(bool* quit) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *quit = true;
                break;
            default:
                break;
        }
    }
}

// gcc monprog.c -o output(.exe) -I include -L lib -lmingw32 -lSDL2main -lSDL2