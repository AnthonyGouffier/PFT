/**
 * @file main.c
 * @author Gouffier Anthony
 * @brief programme principale
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commun.h"
#include "carte.h"

/*
COMPILER SUR WINDOWS :
 clear && gcc .\src\interface.c .\src\fonction_SDL.c -o .\bin\prog  -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && .\bin\prog.exe
*/

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_BUTTONS 5

#define  AREA_WIDTH SCREEN_WIDTH * 0.6 
#define  AREA_HIGH  SCREEN_HEIGHT * 0.65

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    bool visible;
    bool clicked;
    bool hovering;
} Button;

Button CartePkm[NUM_BUTTONS];

/**/
SDL_Rect ArenaZone = {(SCREEN_WIDTH-AREA_WIDTH)/2,0,AREA_WIDTH,AREA_HIGH};

pokemon_t *pokemon=NULL;

void genererCartes(SDL_Renderer* renderer) {
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

void afficherCarteBoutique(SDL_Renderer* renderer) {
    char* images[NUM_BUTTONS] = {"ressources/img/pokeball.jpg", "ressources/img/superball.jpg", "ressources/img/hyperball.jpg", "ressources/img/masterball.jpg", "ressources/img/rapidball.jpg"};
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (CartePkm[i].visible) {
            SDL_Surface* image = IMG_Load(images[i]);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_RenderCopy(renderer, texture, NULL, &CartePkm[i].rect);
            SDL_FreeSurface(image);
            SDL_DestroyTexture(texture);
        }
    }
}

void detruireCarteBoutique(int mouseX, int mouseY) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (CartePkm[i].visible && SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &CartePkm[i].rect)) {
            CartePkm[i].visible = 0;
            CartePkm[i].clicked = 1;
            printf("La carte %d a été cliquée !\n", i+1);
            // Enlever indiceRarete Or dans la structure du joueur;
        }
    }
}

int main(int argc, char* argv[]) {
    initialiserModules();
    pokemon_t* pokemon = createPkmDatabase(1);

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("PFT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if ( window == NULL){ 
        SDL_Log("Creation fenetre: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Erreur de création du renderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Charger l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("ressources/img/background.jpg");
    SDL_Surface* arenaSurface = IMG_Load("ressources/img/PlateauDeJeu.png");

    // Créer la texture de fond
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_Texture* arena = SDL_CreateTextureFromSurface(renderer, arenaSurface);

    // Libérer la surface, qui n'est plus nécessaire
    SDL_FreeSurface(backgroundSurface);

    SDL_FreeSurface(arenaSurface);


    // Vérifier texture
    if (!backgroundTexture) {
        SDL_Log("Erreur de création de la texture d'arrière-plan : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!arena) {
        SDL_Log("Erreur de création de la texture de l'anere : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

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
    
    // Initialisation des boutons

    carteBoutique  bouton1=genererCartePkmBoutique( *pokemon , renderer , window  , 500 , 500 );
    genererCartes(renderer);
    afficherCarteBoutique(renderer);
    
    // Boucle principale
    SDL_Event event;
    bool quit = false;
    int mouseX=0, mouseY=0;
    while (!quit) {

    // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                //Si la souris se situe
                case SDL_MOUSEMOTION:
                     mouseX = event.motion.x;
                     mouseY = event.motion.y;

                    if (mouseX >= BtnActu.rect.x && mouseX <= BtnActu.rect.x + BtnActu.rect.w && mouseY >= BtnActu.rect.y && mouseY <= BtnActu.rect.y + BtnActu.rect.h) {
                        BtnActu.hovering = true;
                        printf("La souris se trouve sur le bouton d'actualisation\n");
                        /*hover sur le bouton selectionné*/
                    } else {
                        BtnActu.hovering = false;
                    }
                    break;
                //Si clic souris
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &BtnActu.rect)) {
                            genererCartes(renderer);
                            printf("Bouton Actualiser cliqué !\n");
                            // Enlever 2 or dans la structure du joueur
                        }
                        else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &AcheterNiveau.rect)) {
                            printf("+4 exp !\n");
                            // Enlever 4 or dans la struct joueur
                            // Ajouter 4 point de XP dans la structure joueur
                        }
                        else {
                            detruireCarteBoutique(mouseX, mouseY);
                        }
                    }
                    break;

            }
        }
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, arena, NULL,&ArenaZone);
        // Afficher les cartes
        afficherCarteBoutique(renderer);

/*----------------RENDU DES BOUTONS-------------------------*/
        if (BtnActu.hovering==true) {
            //Si souris sur BtnActu
            SDL_SetRenderDrawColor(renderer, 0, 50, 50, 255);
            SDL_RenderFillRect(renderer, &BtnActu.rect);
        } else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &BtnActu.rect);
        }
        afficherCartePkmBoutique(bouton1 ,renderer , *pokemon );


        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &AcheterNiveau.rect);

/*------------------RENDU BANC------------------*/
    drawCases(renderer, 50, 50, 200, 800, 6, 2);



    SDL_RenderPresent(renderer);
    }


// Libération des ressources
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();

return 0;
}
