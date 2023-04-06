#include "commun.h"
#include <SDL2/SDL_ttf.h>

void afficher_case_player(SDL_Renderer* renderer, player_t player)
{
    SDL_Rect case_player = {0, 0, 100, 50}; // taille de la case
    SDL_GetRendererOutputSize(renderer, &case_player.w, &case_player.h); // taille de la fenêtre
    case_player.x = case_player.w - case_player.w/4 - case_player.w/8; // position horizontale en bas à droite
    case_player.y = case_player.h - case_player.h/8 - case_player.h/16; // position verticale en bas à droite
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // couleur de fond
    SDL_RenderFillRect(renderer, &case_player); // dessiner la case

    char text[20]; // chaîne de caractères pour afficher les valeurs
    SDL_Color color = {255, 255, 255, 255}; // couleur du texte
    SDL_Surface* surface; // surface temporaire pour le texte
    SDL_Texture* texture; // texture finale pour le texte
    SDL_Rect rect; // rectangle de positionnement du texte
    rect.x = case_player.x + 5; // position horizontale du texte
    rect.y = case_player.y + 5; // position verticale du texte

    // afficher la valeur de "money"
    sprintf(text, "Money : %d", player.money);
    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    // afficher la valeur de "hp"
    sprintf(text, "HP : %d", player.hp);
    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.y += rect.h + 5; // décalage vertical pour le deuxième texte
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // création de la structure player_t
    player_t player = { 100, 50 };

    // affichage de la case avec les valeurs de la structure
    afficher_case_player(renderer, player);

    // boucle principale
    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT)
            break;
    }

    // libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}