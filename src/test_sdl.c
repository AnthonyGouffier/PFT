#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Windowwindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // chargement de l'image de fond
    SDL_Surfacebackground = IMG_Load("images.jpeg");
    SDL_Texture bg_texture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_FreeSurface(background);

    // création de la police TTF et de la texture du bouton "Start"
    TTF_Fontfont = TTF_OpenFont("arial.ttf", 24);
    SDL_Color color = {255, 255, 255};
    SDL_Surface text_surface = TTF_RenderUTF8_Blended(font, "Start", color);
    SDL_Texturetext_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);

    // boucle principale
    SDL_bool done = SDL_FALSE;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        // mise à jour de la taille de la fenêtre
                        SDL_DestroyTexture(bg_texture);
                        background = IMG_Load("images.jpeg");
                        bg_texture = SDL_CreateTextureFromSurface(renderer, background);
                        SDL_FreeSurface(background);
                    }
                    break;
            }
        }
// dessin de l'image de fond
        SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

    SDL_Windowwindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED
        text_rect.x = (WINDOW_WIDTH - text_surface->w) / 2;
        text_rect.y = WINDOW_HEIGHT - 50 - text_surface->h / 2;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;

        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

        SDL_RenderPresent(renderer);
    }

    // nettoyage
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(text_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}