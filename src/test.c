#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Chemins d'accès aux images
const char* IMAGE_PATH1 = "ressources/img/image.jpg";
const char* IMAGE_PATH2 = "ressources/img/image2.jpg";

// Structure pour stocker les données de l'image
typedef struct {
    SDL_Texture* texture;
    SDL_Renderer* renderer;
} ImageData;

// Fonction pour générer la première image
ImageData generateImage1(SDL_Renderer* renderer) {
    ImageData imageData;
    SDL_Surface* imageSurface = IMG_Load(IMAGE_PATH1);
    imageData.texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageData.renderer = renderer;
    return imageData;
}

// Fonction pour générer la deuxième image
ImageData generateImage2(SDL_Renderer* renderer) {
    ImageData imageData;
    SDL_Surface* imageSurface = IMG_Load(IMAGE_PATH2);
    imageData.texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    imageData.renderer = renderer;
    return imageData;
}

// Fonction pour afficher l'image
void renderImage(const ImageData* imageData) {
    SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(imageData->renderer, imageData->texture, NULL, &destRect);
    SDL_RenderPresent(imageData->renderer);
}

int main(int argc, char** argv) {
    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Exemple SDL avec SDL_ttf et SDL_image",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG);

    // Génération de la première image
    ImageData imageData = generateImage1(renderer);

    // Boucle principale
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Redéfinition de imageData avec la deuxième image
        imageData = generateImage2(renderer);

        // Affichage de la deuxième image
        renderImage(&imageData);
    }

    // Libération des ressources
    SDL_DestroyTexture(imageData.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}