#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_BUTTONS 5

typedef struct {
    SDL_Rect rect;
    bool visible;
    bool clicked;
} Button;

Button buttons[NUM_BUTTONS];

int main() {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("PFT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("ressources/img/background.jpg");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Initialisation des boutons
    int buttonWidth = SCREEN_WIDTH / NUM_BUTTONS;
    int buttonHeight = SCREEN_HEIGHT / 8;
    for (int i = 0; i < NUM_BUTTONS; i++) {
        buttons[i].rect.x = i * buttonWidth;
        buttons[i].rect.y = SCREEN_HEIGHT - buttonHeight;
        buttons[i].rect.w = buttonWidth;
        buttons[i].rect.h = buttonHeight;
        buttons[i].visible = true;
        buttons[i].clicked = false;
    }

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
                        for (int i = 0; i < NUM_BUTTONS; i++) {
                            if (buttons[i].visible && SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &buttons[i].rect)) {
                                buttons[i].visible = false;
                                buttons[i].clicked = true;
                            }
                        }
                    }
                    break;
            }
        }

        // Affichage de l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Affichage des boutons
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (buttons[i].visible) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &buttons[i].rect);
            }
        }
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
