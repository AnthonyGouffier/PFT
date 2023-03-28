#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 100;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    SDL_Rect rect;
    bool visible;
    bool hovered;
} Button;

Button buttons[5];

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Boutique Pokémon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur de création du renderer: %s\n", SDL_GetError());
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Erreur d'initialisation de SDL_image: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

void renderButton(Button* button) {
    if (!button->visible) {
        return;
    }
    if (button->hovered) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &button->rect);
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Échec de l'initialisation.\n");
    } else {
        bool quit = false;
        SDL_Event e;
        int borderSize = SCREEN_WIDTH / 10;
        int buttonAreaHeight = (int)(SCREEN_HEIGHT * 0.15); // 15% de l'espace de la fenêtre en bas
        SDL_Rect redSurface = {borderSize, SCREEN_HEIGHT - buttonAreaHeight, SCREEN_WIDTH - (borderSize * 2), buttonAreaHeight};
        int buttonSpacing = (redSurface.w - (5 * BUTTON_WIDTH)) / 6;

        for (int i = 0; i < 5; i++) {
            buttons[i].rect.x = redSurface.x + buttonSpacing + (i * (BUTTON_WIDTH + buttonSpacing));
            buttons[i].rect.y = redSurface.y + (redSurface.h - BUTTON_HEIGHT) / 2;
            buttons[i].rect.w = BUTTON_WIDTH;
            buttons[i].rect.h = BUTTON_HEIGHT;
            buttons[i].hovered = false;
            buttons[i].visible = true;
        }

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_MOUSEMOTION) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    for (int i = 0; i < 5; i++) {
                        buttons[i].hovered = SDL_PointInRect((SDL_Point*)&(SDL_Point){mouseX, mouseY}, &buttons[i].rect);
                    }
                } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    for (int i = 0; i < 5; i++) {
                        if (buttons[i].hovered && buttons[i].visible) {
                            buttons[i].visible = false;
                            printf("Bouton %d cliqué\n", i + 1);
                        }
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &redSurface);
            for (int i = 0; i < 5; i++) {
                renderButton(&buttons[i]);
            }
            SDL_RenderPresent(renderer);
        }
    }
    close();
    return 0;
}