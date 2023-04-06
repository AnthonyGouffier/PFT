#include "commun.h"




void afficher_case_player(SDL_Renderer* renderer, TTF_Font* font, player_t player) {
    // Récupération des dimensions de la fenêtre
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    
    // Dimensions et position de la case
    int case_w = 150;
    int case_h = 50;
    int case_x = w - case_w;
    int case_y = h - case_h;
    
    // Couleur de fond de la case
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect case_rect = { case_x, case_y, case_w, case_h };
    SDL_RenderFillRect(renderer, &case_rect);
    
    // Couleur du texte
    SDL_Color color = { 0, 0, 0 };
    
    // Affichage de l'argent
    char money_text[50];
    snprintf(money_text, 50, "Money: %d", player.money);
    SDL_Surface* surface = TTF_RenderText_Solid(font, money_text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect money_rect = { case_x + 10, case_y + 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &money_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    
    // Affichage des points de vie
    char hp_text[50];
    snprintf(hp_text, 50, "HP: %d", player.hp);
    surface = TTF_RenderText_Solid(font, hp_text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect hp_rect = { case_x + 10, case_y + 30, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &hp_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

