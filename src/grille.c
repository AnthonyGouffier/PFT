#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_SIZE = 52;
const int BUTTON_MARGIN = 5;
const int GRID_ROWS = 6;
const int GRID_COLUMNS = 6;


void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    // Applique la texture à la zone définie par le rectangle du bouton
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}

void swapButtonImages(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* button1Rect, SDL_Rect* button2Rect) {
    // Création d'une surface pour stocker l'image du premier bouton
    SDL_Surface* button1Surface = SDL_CreateRGBSurface(0, button1Rect->w, button1Rect->h, 32, 0, 0, 0, 0);

    // Copie de l'image du premier bouton sur la surface
    SDL_RenderReadPixels(renderer, button1Rect, SDL_PIXELFORMAT_ARGB8888, button1Surface->pixels, button1Surface->pitch);

    // Création d'une texture à partir de la surface
    SDL_Texture* button1Texture = SDL_CreateTextureFromSurface(renderer, button1Surface);

    // Libération de la surface
    SDL_FreeSurface(button1Surface);

    // Copie de l'image du deuxième bouton sur le premier bouton
    SDL_RenderCopy(renderer, imageTexture, button2Rect, button1Rect);

    // Copie de l'image du premier bouton sur le deuxième bouton
    SDL_RenderCopy(renderer, button1Texture, NULL, button2Rect);

    // Libération de la texture du premier bouton
    SDL_DestroyTexture(button1Texture);
}

SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    SDL_Rect buttonRect;
    buttonRect.x = bouttonx;
    buttonRect.y = bouttony;
    buttonRect.w = BUTTON_SIZE;
    buttonRect.h = BUTTON_SIZE;
    return buttonRect;
}


int main(int argc, char* args[]) {
    // Initialisation de la SDL et des bouton sdl
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Rect bouton1;
    SDL_Rect bouton2;

    // Création d'une fenêtre
    SDL_Window* window = SDL_CreateWindow("Grille de boutons SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZE + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZE + BUTTON_MARGIN) - BUTTON_MARGIN;

    // initialise les image
    SDL_Surface* buttonSurface = IMG_Load("../res/bouton.jpeg");
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    SDL_Surface* buttonSurface2 = IMG_Load("../res/index.png");
    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_FreeSurface(buttonSurface2);

    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("../res/gigarena.jpg");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    // Calcul de la position de la grille pour la centrer au milieu de la fenêtre
    int gridX = (SCREEN_WIDTH - gridWidth) / 2;
    int gridY = (SCREEN_HEIGHT - gridHeight) / 2;

    // Boucle principale
    int quit = 0;
    int cpt_deplacement=0; //compteur pour que tout les 2 bouton on switch les deplacement
    while (!quit) {
        int mouseX, mouseY;
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Vérification si le clic est sur un bouton
                    SDL_GetMouseState(&mouseX, &mouseY);
                    for (int row = 0; row < GRID_ROWS; row++) {
                        for (int column = 0; column < GRID_COLUMNS; column++) {
                            int buttonX = gridX + column * (BUTTON_SIZE + BUTTON_MARGIN);
                            int buttonY = gridY + row * (BUTTON_SIZE + BUTTON_MARGIN);
                            if (mouseX >= buttonX && mouseX <= buttonX + BUTTON_SIZE && mouseY >= buttonY && mouseY <= buttonY + BUTTON_SIZE) {                          
                                    printf("Bouton (%d, %d) cliqué !\n", row, column);
                                    if(cpt_deplacement==0){
                                        bouton1=getButtonRect(buttonX,buttonY);
                                        cpt_deplacement++;
                                    }else{
                                        cpt_deplacement=0;
                                        bouton2=getButtonRect(buttonX,buttonY);
                                    }

                            }
                        }
                    }
                    break;
            }
        }

        // Effacer le renderer
        SDL_RenderClear(renderer);

        // Dessiner l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Dessiner les boutons de la grille
        for (int row = 0; row < GRID_ROWS; row++) {
            for (int column = 0; column < GRID_COLUMNS; column++) {
                // Calcul de la position du bouton dans la grille
                int buttonX = gridX + column * (BUTTON_SIZE + BUTTON_MARGIN);
                int buttonY = gridY + row * (BUTTON_SIZE + BUTTON_MARGIN);

                // Dessiner le rectangle du bouton
                SDL_Rect buttonRect = { buttonX, buttonY, BUTTON_SIZE, BUTTON_SIZE };
                SDL_RenderFillRect(renderer, &buttonRect);
                SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
                setButtonImage(renderer,buttonTexture2,&bouton1);
                setButtonImage(renderer,buttonTexture2,&bouton2);
            }
        }

        // Afficher le renderer à l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyage des ressources
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}