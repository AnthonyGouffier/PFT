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
#include "boutique.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_BUTTONS 5

#define  AREA_WIDTH SCREEN_WIDTH * 0.60
#define  AREA_HIGH  SCREEN_HEIGHT * 0.60

#define WIDTH_STATS   SCREEN_WIDTH / 8
#define HEIGHT_STATS  SCREEN_HEIGHT/ 12

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

/**/
SDL_Rect ArenaZone = {( SCREEN_WIDTH - AREA_WIDTH) / 2 , 0 , AREA_WIDTH , AREA_HIGH };


/*
pokemon_t genererCartes(SDL_Renderer* renderer , SDL_Window* window, pokemon_t* tabCartes) {

 //   "parametres des boutons (taille espacement...)"*/

carteBoutique* genererTabCarte(pokemon_t* pokemonListe, SDL_Renderer* renderer, SDL_Window* window) {
    const int buttonWidth = (SCREEN_WIDTH * 0.6) / NUM_BUTTONS;
    const int buttonHeight = SCREEN_HEIGHT / 6;
    int buttonSpacing = SCREEN_WIDTH * 0.2 / (NUM_BUTTONS + 1);
    int buttonOffset = (SCREEN_WIDTH * 0.6) / (NUM_BUTTONS + 1);
    int firstButtonX = buttonOffset + buttonSpacing;

    // Allouer dynamiquement de la mémoire pour le tableau de structures
    carteBoutique* tabcarte = malloc(NUM_BUTTONS * sizeof(carteBoutique));
    if (tabcarte == NULL) {
        // Gestion de l'erreur si l'allocation échoue
        printf("Erreur d'allocation de mémoire\n");
        return NULL; // ou effectuer une autre action appropriée
    }
    for (int i=0; i < NUM_BUTTONS; i++) {
        // tabcarte[0] = genererCartePkmBoutique(pokemonListe[0], renderer, window , SCREEN_WIDTH * 0.1 / (NUM_BUTTONS + 1), (SCREEN_HEIGHT - buttonHeight) , buttonWidth , buttonHeight) ;
        // printPkm(pokemonListe[i]);
        tabcarte[i] = genererCartePkmBoutique(pokemonListe[i], renderer, window , firstButtonX + i*(buttonWidth+(SCREEN_WIDTH * 0.0125)), (SCREEN_HEIGHT*0.975 - buttonHeight ) , buttonWidth , buttonHeight) ;
    }
    return tabcarte;
}

int main(int argc, char* argv[]) {
    printf("Bienvenue sur PFT !\n");
    //Initilisation 
    srand( time( NULL ) );

    //Initilisation SDL 
    initialiserModules();

    //Creation d'un joueur
    int nbjoueur;
    printf("Saisir nombre de joueurs :"); scanf("%d",&nbjoueur);
    player_t* TabJoueurs = malloc ( sizeof ( player_t ) * nbjoueur);
    for(int i =0 ; i < nbjoueur ; i++){
        createPlayer((TabJoueurs+i),i+1);
        stat_player(&(TabJoueurs[i]));
    }

    //Creation de la database
    pokemon_t* database= genererationDatabase();
    pokemon_t *listepokemon = genererBoutique(&TabJoueurs[0],database);
    //afficherEquipe(listepokemon,100);

    afficherEquipe(listepokemon,5);    //Creation d'un joueur
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

    // Charger les images de l'ATH


    //image de fond
    //button boutiques
    SDL_Surface* backgroundSurface = IMG_Load("ressources/img/background.png");
    SDL_Surface* arenaSurface = IMG_Load("ressources/img/plateaudejeu.png");
    SDL_Surface* boutonxpSurface = IMG_Load("ressources/img/Bouton_Achat_XP.png");
    SDL_Surface* boutonxphoveredSurface = IMG_Load("ressources/img/Bouton_Achat_XP_hovered.png");
    SDL_Surface* boutonactuSurface = IMG_Load("ressources/img/Bouton_Actu.png");
    SDL_Surface* boutonactuhoveredSurface = IMG_Load("ressources/img/Bouton_Actu_hovered.png");

    // Créer la texture de fond
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_Texture* arena = SDL_CreateTextureFromSurface(renderer, arenaSurface);

    SDL_Texture* boutonxpTexture = SDL_CreateTextureFromSurface(renderer,boutonxpSurface);
    SDL_Texture* boutonxphoveredTexture = SDL_CreateTextureFromSurface(renderer,boutonxphoveredSurface);
    SDL_Texture* boutonactuTexture = SDL_CreateTextureFromSurface(renderer,boutonactuSurface);
    SDL_Texture* boutonactuhoveredTexture = SDL_CreateTextureFromSurface(renderer,boutonactuhoveredSurface);

    // Libérer la surface, qui n'est plus nécessaire
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(arenaSurface);
    SDL_FreeSurface(boutonxpSurface);
    SDL_FreeSurface(boutonxphoveredSurface);
    SDL_FreeSurface(boutonactuSurface);
    SDL_FreeSurface(boutonactuhoveredSurface);

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
    
    //Initialisation du rendu des PV
    plaqueStat renduStat = CreerGraphStats( renderer , window , &TabJoueurs[0] , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2  ,  WIDTH_STATS  , HEIGHT_STATS );



    // Boucle principale
    bool quit = false;
    int mouseX=0, mouseY=0;
    SDL_Event event;
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
                            //free(listepokemon);
                             detruireCartePkmBoutique(tabcarte[0]);
                            listepokemon = genererBoutique(&TabJoueurs[0],database);
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
                            TabJoueurs[0].hp--;
                            renduStat = CreerGraphStats( renderer , window , &TabJoueurs[0] , SCREEN_WIDTH/2 , SCREEN_HEIGHT/2  ,  WIDTH_STATS  , HEIGHT_STATS );
                            for (int i = 0; i < nbjoueur; i++){
                                stat_player(&(TabJoueurs[i]));
                            }
                        }
                        for (int i = 0; i < 5; i++) {
                            if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &tabcarte[i].blackRect) && tabcarte[i].click==0) {
                                printf("la carte numero %d à été cliqué\n",i);
                                acheterCarte(&TabJoueurs[0],&tabcarte[i],&listepokemon[i]);
                            }
                        }
                break;
                }
            }
        }

        //rendu de l'arriere plan
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, arena, NULL,&ArenaZone);

        // Afficher les cartes

/*--------------------RENDU DES BOUTONS-------------------------*/
        if (BtnActu.hovering==true) {
            //Si souris sur BtnActu
            SDL_RenderCopy(renderer,boutonactuhoveredTexture,NULL,&BtnActu);
        } else{
            SDL_RenderCopy(renderer,boutonactuTexture,NULL,&BtnActu);
        }
        SDL_RenderCopy(renderer,boutonxpTexture,NULL,&AcheterNiveau.rect);
/*-------------------------FIN-------------------------*/
        //affiche les cartes si non clické
        for (int i = 0; i < 5; i++) {
            if(tabcarte[i].click==0){
                afficherCartePkmBoutique(tabcarte[i],renderer,listepokemon[i]);
            }
        }

/*------------------RENDU BANC------------------*/
   // drawCases(renderer, 50, 50, 200, 800, 6, 2);
    AfficherGraphStats(window,renderer,renduStat,&TabJoueurs[0]);

    SDL_RenderPresent(renderer);
    }



    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}