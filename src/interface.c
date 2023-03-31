#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_BUTTONS 5

typedef struct {    
    SDL_Rect rect;
    bool visible;
    bool clicked;
} Button;

Button CartePkm[NUM_BUTTONS];

void genererCartes() {
    /* "parametres des boutons (taille espacement...)"*/
    int buttonWidth = (SCREEN_WIDTH * 0.6) / NUM_BUTTONS;
    int buttonHeight = SCREEN_HEIGHT / 6;
    int buttonSpacing = SCREEN_WIDTH * 0.1 / (NUM_BUTTONS + 1);
    int buttonOffset = (SCREEN_WIDTH * 0.5) / (NUM_BUTTONS + 1);
    int firstButtonX = buttonOffset + buttonSpacing;

    for (int i = 0; i < NUM_BUTTONS; i++) {
        CartePkm[i].rect.x = firstButtonX + i * buttonWidth + i * buttonSpacing;
        CartePkm[i].rect.y = SCREEN_HEIGHT * 0.8125;
        CartePkm[i].rect.w = buttonWidth;
        CartePkm[i].rect.h = buttonHeight;
        CartePkm[i].visible = true;
        CartePkm[i].clicked = false;
    }
}

void afficherCartes(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (CartePkm[i].visible) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &CartePkm[i].rect);
        }
    }
}

int main(int argc, char* argv[]) {

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_VIDEO) != 0){
        SDL_Log("Erreur initialisation SDL : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("PFT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation des boutons
    genererCartes();
    afficherCartes(renderer);

    // Bouton d'actualisation de la boutique
    Button BtnActu;
    BtnActu.rect.x =  SCREEN_WIDTH * 0.8;
    BtnActu.rect.y =  SCREEN_HEIGHT * 0.91;
    BtnActu.rect.w = SCREEN_WIDTH / 8;
    BtnActu.rect.h = SCREEN_HEIGHT / 12;
    BtnActu.visible = true;
    BtnActu.clicked = false;

    // Bouton d'achat de niveau
    Button AcheterNiveau;
    AcheterNiveau.rect.x =  SCREEN_WIDTH * 0.8;
    AcheterNiveau.rect.y =  SCREEN_HEIGHT * 0.8;
    AcheterNiveau.rect.w = SCREEN_WIDTH / 8;
    AcheterNiveau.rect.h = SCREEN_HEIGHT / 12;
    AcheterNiveau.visible = true;
    AcheterNiveau.clicked = false;

    // Boucle principale
    SDL_Event event;
    bool quit = false;
    while (!quit) {
    // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;

                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &BtnActu.rect)) {
                            genererCartes();
                            afficherCartes(renderer);
                            printf("Bouton Actualiser cliqué !\n");
                            // Enlever 2 or dans la structure du joueur
                        }
                        else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &AcheterNiveau.rect)) {
                            printf("+4 exp !\n");
                            // Enlever 4 or dans la struct joueur
                            // Ajouter 4 point de XP dans la structure joueur
                        }
                        else {
                            for (int i = 0; i < NUM_BUTTONS; i++) {
                                if (CartePkm[i].visible && SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &CartePkm[i].rect)) {
                                    CartePkm[i].visible = false;
                                    CartePkm[i].clicked = true;
                                    printf("La carte %d a été cliquée !\n", i+1);
                                    // Enlever indiceRarete or dans la structure du joueur;
                                }
                            }
                        }
                    }
                break;
            }
        }
    
    // Afficher les cartes
    afficherCartes(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &AcheterNiveau.rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &BtnActu.rect);
    SDL_RenderPresent(renderer);
}

// Libération des ressources
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();

return 0;
}
