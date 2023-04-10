#include "joueur.h"
#include "commun.h"
/*
gcc .\src\afficher_stat_joueur.c .\src\joueur.c .\src\fonction.c .\src\database.c -o .\bin\test -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && .\bin\test.exe
*/
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define WIDTH_PLAQUE 600 / 4
#define HIGHT_PLAQUE 215 / 4


typedef struct 
{
    SDL_Rect rectDest;
    SDL_Rect rectTexte;
    SDL_Rect rectNiv;
    SDL_Rect rectHp;
    SDL_Rect rectXp;
    SDL_Texture* nameT;
    SDL_Texture* lvlT;
    SDL_Texture* plaqueT;
}plaqueStat;


int main(int arc,char** argv){

    initialiserModules();
    player_t *joueur;
    createPlayer(&joueur,1);
    stat_player(&joueur);
    plaqueStat plaque;
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

    int x = 0 ;
    int y = 0 ;
    SDL_Color textColor = {255,255,255};
    // Chargement de la police Pokemon
    TTF_Font* font = TTF_OpenFont("ressources/font/Pokemon_Classic.ttf",12);
    if (!font) {
        printf("Erreur de chargement de la police: %s\n", TTF_GetError());
        // Gestion de l'erreur
    }

    //chargement de l'image
    SDL_Surface* plaqueS = IMG_Load("ressources/img/plaquestats.png");
    if(!plaqueS) {
        printf("Erreur de chargement de l'image : %s", IMG_GetError());
    }
    SDL_Texture* plaqueT = SDL_CreateTextureFromSurface(renderer, plaqueS);
    // Vérifier texture
    if (!plaqueT) {
        SDL_Log("Erreur de création de la texture d'arrière-plan : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_FreeSurface(plaqueS);


    SDL_Surface* nameS = TTF_RenderText_Solid(font,joueur->nom,textColor);
    if (!nameS) {
        printf("Erreur de surface du texte: %s\n", TTF_GetError());
    }

    SDL_Surface* nivS = TTF_RenderText_Solid(font,joueur->niveau,textColor);
    if (!nivS) {
        printf("Erreur de surface du texte: %s\n", TTF_GetError());
    }

    // Création d'une texture à partir de la surface de texte
    plaque.nameT = SDL_CreateTextureFromSurface(renderer,nivS);
    plaque.lvlT = SDL_CreateTextureFromSurface(renderer,nivS);


    //creation des rectangles
    //rectangle de position
    

 
    printf("position du rectangle conteneur : %d %d\n",(x - WIDTH_PLAQUE), (y - HIGHT_PLAQUE));

    /*INITIALISATION DES RECTANGLES*/                                               /*et stockage des val dans la structure*/
    SDL_Rect temp0= { x , y ,WIDTH_PLAQUE,HIGHT_PLAQUE};                                    plaque.rectDest=temp0;
    SDL_Rect temp1= {temp0.x * 0.02 , temp0.y * 0.19 , temp0.w * 0.84, temp0.y * 0.28};     plaque.rectTexte=temp1;
    SDL_Rect temp2= {temp0.x * 0.75 , temp0.y * 0.55 , temp0.w * 0.167, temp0.y * 0.265};   plaque.rectNiv=temp2;
    SDL_Rect temp3= {temp0.x * 0.17 , temp0.y * 0.633 , temp0.w * 0.53, temp0.y * 0.105};   plaque.rectHp=temp3;
    SDL_Rect temp4= {temp0.x * 0.06 , temp0.y * 0.895 , temp0.w * 0.82, temp0.y * 0.07};    plaque.rectXp=temp4;
}
    
void afficherPlaque(SDL_Renderer* renderer, SDL_Window* window ,plaqueStat* plaque ){
    /*RENDU*/

    //text
    SDL_RenderFillRect(renderer, &plaque->rectTexte);

    //pv
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &plaque->rectHp);

    //xp
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &plaque->rectXp);

    
    
    SDL_RenderCopy(renderer,plaque->plaqueT,NULL,&plaque->rectDest);


    // Libération des ressources

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}   
