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
#include "entites.h"
#include "carte.h"
#include "joueur.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_BUTTONS 5

#define  AREA_WIDTH SCREEN_WIDTH * 0.6 
#define  AREA_HIGH  SCREEN_HEIGHT * 0.65

#define WIDTHX_CARTE 200
#define HIGHTY_CARTE 150

typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    bool visible;
    bool clicked;
    bool hovering;
} Button;

Button CartePkm[NUM_BUTTONS];
carteBoutique tabCartes[NUM_BUTTONS]; 

/**/
SDL_Rect ArenaZone = {(SCREEN_WIDTH-AREA_WIDTH)/2,0,AREA_WIDTH,AREA_HIGH};


/*
pokemon_t genererCartes(SDL_Renderer* renderer , SDL_Window* window, pokemon_t* tabCartes) {

 //   "parametres des boutons (taille espacement...)"*/

pokemon_t *pokemon=NULL;

carteBoutique* genererTabCarte(pokemon_t* pokemonListe, SDL_Renderer* renderer, SDL_Window* window) {
    const int buttonWidth = (SCREEN_WIDTH * 0.6) / NUM_BUTTONS;
    const int buttonHeight = SCREEN_HEIGHT / 6;
    int buttonSpacing = SCREEN_WIDTH * 0.2 / (NUM_BUTTONS + 1);
    int buttonOffset = (SCREEN_WIDTH * 0.6) / (NUM_BUTTONS + 1);
    int firstButtonX = buttonOffset + buttonSpacing;

    // Allouer dynamiquement de la mémoire pour le tableau de structures
    carteBoutique* tabCarte = malloc(NUM_BUTTONS * sizeof(carteBoutique));
    if (tabCarte == NULL) {
        // Gestion de l'erreur si l'allocation échoue
        printf("Erreur d'allocation de mémoire\n");
        return NULL; // ou effectuer une autre action appropriée
    }
    for (int i=0; i < NUM_BUTTONS; i++) {
        // tabCarte[0] = genererCartePkmBoutique(pokemonListe[0], renderer, window , SCREEN_WIDTH * 0.1 / (NUM_BUTTONS + 1), (SCREEN_HEIGHT - buttonHeight) , buttonWidth , buttonHeight) ;
        //   printPkm(pokemonListe[i]);
        tabCarte[i] = genererCartePkmBoutique(pokemonListe[i], renderer, window , firstButtonX + i*(buttonWidth+(SCREEN_WIDTH * 0.0125)), (SCREEN_HEIGHT*0.975 - buttonHeight ) , buttonWidth , buttonHeight) ;
    }
    return tabCarte;
}

/*
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
*/

int main(int argc, char* argv[]) {
    printf("Bienvenue sur PFT !\n");
    //Initilisation SDL 
    initialiserModules();

    //Creation d'un joueur

    int nbjoueur;
    printf("Saisir nombre de joueurs :"); scanf("%d",&nbjoueur);
    player_t* TabJoueurs = malloc ( sizeof ( player_t ) * nbjoueur);
    for(int i =0 ; i < nbjoueur ; i++){
        player_t* joueur1;
        createPlayer((TabJoueurs+i),i+1);
        stat_player(&(TabJoueurs[i]));
    }



    //Creation de la database
    pokemon_t* listepokemon= genererationDatabase();
    //afficherEquipe(listepokemon,100);

    //pokemon_t* listepokemon = createPkmDatabase(5,2);
    afficherEquipe(listepokemon,5);
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
    carteBoutique *tabcarte=genererTabCarte(listepokemon,renderer,window);   
    //carteBoutique carte1 = genererCartePkmBoutique(listepokemon[0], renderer, window, 800, 800,WIDTHX_CARTE,HIGHTY_CARTE);
    //carteBoutique carte2 = genererCartePkmBoutique(listepokemon[1], renderer, window, 500, 500,WIDTHX_CARTE-50,HIGHTY_CARTE+100);
    
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
                //track la position de la souris
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
                //Attend un clic souris
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &BtnActu.rect)) {
                            //genererCartes(renderer,window);
                            printf("Bouton Actualiser cliqué !\n");
                                for (int i = 0; i < 5; i++) {
                                    tabcarte[i].click=0;
                                    printf("Carte %d remise en état visible\n",i);
                                    printf("Le joueur perd 2 Or\n Or restant : (a remplir)");
                                 }
                            //genererTabCarte(pokemon,renderer,window);
                            // Enlever 2 or dans la structure du joueur
                        }
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &AcheterNiveau.rect)) {
                            acheterNiveauXP(&TabJoueurs[0]);// Enlever 4 or dans la struct joueur
                            for (int i = 0; i < nbjoueur; i++)
                            {
                            stat_player(&(TabJoueurs[i]));
                            }
                        }
                        for (int i = 0; i < 5; i++) {
                            if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &tabcarte[i].blackRect) && tabcarte[i].click==0) {
                                printf("la carte numero %d à été cliqué\n",i);
                                acheterCarte(&TabJoueurs[0],&tabCartes[i],&pokemon[i]);
                            }
                        }
                break;
                }
            }
        }
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, arena, NULL,&ArenaZone);
        // Afficher les cartes

      //  afficherCartePkmBoutique(carte1,renderer ,listepokemon[0]);
      //  afficherCartePkmBoutique(carte2,renderer , listepokemon[1]);

/*----------------RENDU DES BOUTONS-------------------------*/
        if (BtnActu.hovering==true) {
            //Si souris sur BtnActu
            SDL_SetRenderDrawColor(renderer, 0, 50, 50, 255);
            SDL_RenderFillRect(renderer, &BtnActu.rect);
        } else{
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &BtnActu.rect);
        }

        //affiche les cartes si non clické
        for (int i = 0; i < 5; i++) {
            if(tabcarte[i].click==0){
                afficherCartePkmBoutique(tabcarte[i],renderer,listepokemon[i]);
            }
        }

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