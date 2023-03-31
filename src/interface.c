#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_BUTTONS 5

typedef struct {    
    SDL_Rect rect;
    bool visible;
    bool clicked;
} Button;

Button crtboutique[NUM_BUTTONS];

void genererCartes() {
    int buttonWidth = (SCREEN_WIDTH * 0.6) / NUM_BUTTONS;
    int buttonHeight = SCREEN_HEIGHT / 6;
    int buttonSpacing = SCREEN_WIDTH * 0.1 / (NUM_BUTTONS + 1);
    int buttonOffset = (SCREEN_WIDTH * 0.1) / (NUM_BUTTONS + 1);
    int firstButtonX = buttonOffset + buttonSpacing;

    for (int i = 0; i < NUM_BUTTONS; i++) {
        crtboutique[i].rect.x = firstButtonX + i * buttonWidth + i * buttonSpacing;
        crtboutique[i].rect.y = SCREEN_HEIGHT - buttonHeight;
        crtboutique[i].rect.w = buttonWidth;
        crtboutique[i].rect.h = buttonHeight;
        crtboutique[i].visible = true;
        crtboutique[i].clicked = false;
    }
}

void afficherCartes(SDL_Renderer* renderer){
            // Affichage des boutons
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (crtboutique[i].visible) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &crtboutique[i].rect);
            }
        }
        //SDL_RenderPresent(renderer);
}
int main() {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("PFT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation des boutons
    genererCartes();
    afficherCartes(renderer);

    /*Bouton d'actualisation de la boutique*/
    Button BtnActu;
    BtnActu.rect.x = 1000;
    BtnActu.rect.y = 650;
    BtnActu.rect.w =  SCREEN_WIDTH/ 8; // Largeur
    BtnActu.rect.h = SCREEN_HEIGHT /12; // Hauteur
    BtnActu.visible = true;
    BtnActu.clicked = false;

    /*Bouton d'actualisation de la boutique*/
    Button AcheterNiveau;
    AcheterNiveau.rect.x = 1000;
    AcheterNiveau.rect.y = 575;
    AcheterNiveau.rect.w =  SCREEN_WIDTH/ 8; // Largeur
    AcheterNiveau.rect.h = SCREEN_HEIGHT /12; // Hauteur
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
                /*Si on appuie sur le bouton on recharge les cartes*/
            if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &BtnActu.rect)) {
                genererCartes();
                afficherCartes(renderer);
                printf("Bouton Actualiser cliqué !\n");
                //enlever 2 or dans la structure du joueur
            }
        else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &AcheterNiveau.rect)) {
            printf("+4 exp !\n");
            //Enlever 4 or dans la struct joueur
            //Ajouter 4 point de XP dans la structure joueur
        }
        else {
            for (int i = 0; i < NUM_BUTTONS; i++) {
                if (crtboutique[i].visible && SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &crtboutique[i].rect)) {
                    crtboutique[i].visible = false;
                    crtboutique[i].clicked = true;
                    printf("La carte %d a été cliquée !\n", i+1);
                    //Enlever indiceRarete or dans la structure du joueur;
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
        SDL_RenderFillRect(renderer,&AcheterNiveau.rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer,&BtnActu.rect);
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
