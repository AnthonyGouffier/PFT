#include "grille.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_SIZE = 40;
const int BUTTON_MARGIN = 15;
const int GRID_ROWS = 6;
const int GRID_COLUMNS = 6;




void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    // Applique la texture à la zone définie par le rectangle du bouton
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}

typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;


SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    Button buttonRect;
    buttonRect.rect.x = bouttonx;
    buttonRect.rect.y = bouttony;
    buttonRect.rect.w = BUTTON_SIZE;
    buttonRect.rect.h = BUTTON_SIZE;
    
    return buttonRect.rect;
}



int main(int argc, char* args[]) {


    // Initialisation de la SDL et des bouton sdl
    initialiserModules();

    Button bouton1;
    Button bouton2;
    Button buttonRect;



    // Création d'une fenêtre
    SDL_Window* window = SDL_CreateWindow("Grille de boutons SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZE + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZE + BUTTON_MARGIN) - BUTTON_MARGIN;

    // initialise les image
    SDL_Surface* buttonSurface2 = IMG_Load("ressources/img/image.jpg");
    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_FreeSurface(buttonSurface2);

    SDL_Surface* Surfacetampon;


    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("ressources/img/PlateauDeJeu.png");
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
    int cpt=0; //compteur pour que tout les 2 bouton on switch les deplacement

    pokemon_t *  plateau[GRID_ROWS][GRID_COLUMNS];
    pokemon_t *  poke=createPkmDatabase(1);
    poke->alive=1;
    // initialise les image du poke de test 
    /*
    SDL_Texture* buttonTexture3 = SDL_CreateTextureFromSurface(renderer, buttonSurface3);
    SDL_FreeSurface(buttonSurface3);
    */
    //pokemon test 

    //place les poke de test
    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            plateau[i][j] = malloc(sizeof(pokemon_t));
            plateau[i][j]=initialiserPkm(plateau[i][j]);
        }
    }

    plateau[3][3]=poke;
    plateau[4][4]=poke;

    printPkm(*poke);


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
                                   /* if(cpt==0){
                                        bouton1.rect=getButtonRect(buttonX,buttonY);
                                        bouton1.texture=buttonRect.texture;
                                        cpt++;
                                    }else{
                                        cpt=0;
                                        bouton2.rect=getButtonRect(buttonX,buttonY);
                                        bouton2.texture=buttonRect.texture;
                                    }*/

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
                buttonRect.rect.x =  buttonX;   
                buttonRect.rect.y = buttonY;
                buttonRect.rect.w =  BUTTON_SIZE;
                buttonRect.rect.h = BUTTON_SIZE;
                if(plateau[row][column]->alive==1){
                    SDL_Texture* Texturetampon = SDL_CreateTextureFromSurface(renderer, plateau[row][column]->imgSurface);
                    setButtonImage(renderer,Texturetampon,&buttonRect.rect);
                    SDL_DestroyTexture(Texturetampon);
                }
            }
        }


        // Afficher le renderer à l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyage des ressources
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


//charge la texture du pok
                    /*Texturetampon = SDL_CreateTextureFromSurface(renderer,);
                    SDL_FreeSurface(plateau[row][column]->imgSurface);
                    setButtonImage(renderer,Texturetampon,&buttonRect.rect);*/