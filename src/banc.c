#include <SDL.h>

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

/*int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Exemple d'utilisation de la fonction drawCases", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawCases(renderer, 50, 50, 200, 800, 6, 2);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/
