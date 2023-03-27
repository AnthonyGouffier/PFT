#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* image = IMG_Load("example.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    SDL_RenderClear(renderer);

    SDL_Rect rect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
