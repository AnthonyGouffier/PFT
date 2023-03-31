#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* args[]) {
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    int window_height=480;
    int window_width=640;
    // Création d'une fenêtre
    SDL_Window* window = SDL_CreateWindow("Bouton SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("../res/gigarena.jpg");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    // Chargement des image des bouton
    SDL_Surface* buttonSurface1 = IMG_Load("../res/bouton.jpeg");
    if (buttonSurface1 == NULL) {
        printf("Erreur de chargement de l'image du bouton : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* buttonSurface2 = IMG_Load("../res/bouton.jpeg");
    if (buttonSurface2 == NULL) {
        printf("Erreur de chargement de l'image du bouton : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* buttonSurface3 = IMG_Load("../res/bouton.jpeg");
    if (buttonSurface3 == NULL) {
        printf("Erreur de chargement de l'image du bouton : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* buttonSurface4 = IMG_Load("../res/bouton.jpeg");
    if (buttonSurface4 == NULL) {
        printf("Erreur de chargement de l'image du bouton : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* buttonSurface5 = IMG_Load("../res/bouton.jpeg");
    if (buttonSurface5 == NULL) {
        printf("Erreur de chargement de l'image du bouton : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* buttonTexture1 = SDL_CreateTextureFromSurface(renderer, buttonSurface1);
    SDL_FreeSurface(buttonSurface1);
    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_FreeSurface(buttonSurface2);
    SDL_Texture* buttonTexture3 = SDL_CreateTextureFromSurface(renderer, buttonSurface3);
    SDL_FreeSurface(buttonSurface3);
    SDL_Texture* buttonTexture4 = SDL_CreateTextureFromSurface(renderer, buttonSurface4);
    SDL_FreeSurface(buttonSurface4);
    SDL_Texture* buttonTexture5 = SDL_CreateTextureFromSurface(renderer, buttonSurface5);
    SDL_FreeSurface(buttonSurface5);

    // Création d'un rectangle pour représenter le bouton
    int coeff_img=75;
    SDL_Rect button1 = { window_width-coeff_img, window_height-coeff_img, coeff_img,coeff_img };
    SDL_Rect button2 = { window_width-coeff_img*2, window_height-coeff_img, coeff_img,coeff_img};
    SDL_Rect button3 = { window_width-coeff_img*3, window_height-coeff_img, coeff_img,coeff_img};
    SDL_Rect button4 = { window_width-coeff_img*4, window_height-coeff_img, coeff_img,coeff_img};
    SDL_Rect button5 = { window_width-coeff_img*5, window_height-coeff_img, coeff_img,coeff_img};

    // Boucle principale
    int quit = 0;
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
                    // Vérification si le clic est sur le bouton
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= button1.x && mouseX <= button1.x + button1.w && mouseY >= button1.y && mouseY <= button1.y + button1.h) {
                        // Le clic est sur le bouton
                        printf("Le bouton a été cliqué !\n");
                    }
                    if (mouseX >= button2.x && mouseX <= button2.x + button2.w && mouseY >= button2.y && mouseY <= button2.y + button2.h) {
                        // Le clic est sur le bouton
                        printf("Le bouton a été cliqué !\n");
                    }
                    if (mouseX >= button3.x && mouseX <= button3.x + button3.w && mouseY >= button3.y && mouseY <= button3.y + button3.h) {
                        // Le clic est sur le bouton
                        printf("Le bouton a été cliqué !\n");
                    }
                    if (mouseX >= button4.x && mouseX <= button4.x + button4.w && mouseY >= button4.y && mouseY <= button4.y + button4.h) {
                        // Le clic est sur le bouton
                        printf("Le bouton a été cliqué !\n");
                    }
                    if (mouseX >= button5.x && mouseX <= button5.x + button5.w && mouseY >= button5.y && mouseY <= button5.y + button5.h) {
                        // Le clic est sur le bouton
                        printf("Le bouton a été cliqué !\n");
                    }
                    break;
            }
        }

        // Effacer le renderer
        SDL_RenderClear(renderer);

        

        // Dessiner l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Dessiner le bouton image
        SDL_RenderCopy(renderer, buttonTexture1, NULL, &button1);
        SDL_RenderCopy(renderer, buttonTexture2, NULL, &button2);
        SDL_RenderCopy(renderer, buttonTexture3, NULL, &button3);
        SDL_RenderCopy(renderer, buttonTexture4, NULL, &button4);
        SDL_RenderCopy(renderer, buttonTexture5, NULL, &button5);

        // Afficher le renderer à l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyage des ressources
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture1);
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(buttonTexture3);
    SDL_DestroyTexture(buttonTexture4);
    SDL_DestroyTexture(buttonTexture5);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}