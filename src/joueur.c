#include <stdio.h>
#include <string.h>
#include "carte.h"
#include "joueur.h"
#include "commun.h"

#define NBMAX_PKM 10

void acheterNiveauXP(player_t *joueur){
    /*Recupere les valeures importantes*/
    if(joueur->alive==true && joueur->money > 4 && joueur->niveau>2 && joueur->niveau < 11 ){
        joueur->xp += 4;
        joueur->money -= 4;

        switch (joueur->niveau)
            {
            case 3:
                if(joueur->xp > 6){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=6;
                } 
                break;
            case 4:
                if(joueur->xp > 10){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=10;
                } 
                break;
            case 5:
                if(joueur->xp > 20){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=20;
                } 
                break;
            case 6:
                if(joueur->xp > 36){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=36;
                } 
                break;
            case 7:
                if(joueur->xp > 56){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=56;
                } 
                break;
            case 8:
                if(joueur->xp > 80){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=80;
                } 
                break;
            case 9:
                if(joueur->xp > 100){
                    joueur->niveau++;
                    printf("Vous passez au niveau %d\n",joueur->niveau);
                    joueur->xp-=100;
                } 
                break;
            default:
                printf("Vous êtes déjà au niveau maximum !\n");
            break;
        }
    }
}


void createPlayer(player_t* joueur, int id){

    printf("Veuillez saisir votre nom : ");
    scanf("%s", joueur->nom);
    joueur->id = id;
    
    int lvlcap_init[8] = {2, 6, 10, 20, 36, 56, 80, 100};
    for (int i = 0; i < 8; i++) {
        joueur->lvlcap[i] = lvlcap_init[i];
    }
    joueur->xp = 0;
    joueur->hp = 100;
    joueur->niveau = 3;
    joueur->money = 1000;
    joueur->interest = 0;
    joueur->alive = true;

    printf("initialisation du tableau...\n");
    //Initialise le tableau à 0
    for(int i=0;i<NBMAX_PKM;i++){
        printf("Case num %d du tableau\n",i);
        joueur->team[i] = initialiserPkm() ;
    }
    stat_player(joueur);
}

int nbPkmTeam(player_t* joueur){
    int nombrePokemons = 0;
    for(int i=0;i<NBMAX_PKM;i++){
        printf("case %d joueur->team[i].id :%d\n",i,joueur->team[i].id);
        if(joueur->team[i].id > 0){
            nombrePokemons++;
        }
    }
    return nombrePokemons;
}

void stat_player(player_t* joueur) {
    printf("Nom : %s\n", joueur->nom);
    printf("ID : %d\n", joueur->id);
    printf("Niveau : %d\n", joueur->niveau);
    printf("XP : %d\n", joueur->xp);
    printf("HP : %d\n", joueur->hp);
    printf("Argent : %d\n", joueur->money);
    printf("Interet : %d\n", joueur->interest);
    printf("Vivant : %s\n", joueur->alive ? "Oui" : "Non");
}

void acheterCarte(player_t* joueur, carteBoutique* carte ,pokemon_t* pokemon){
    //récupération du nombre de pkm de l'équipe
    int nbpkm = nbPkmTeam(joueur);
    printf("nombre de pkm : %d\n",nbpkm);
    printf(" joueur -> alive : %d  joueur->money : %d pokemon->rarete : %d " , joueur->alive , joueur->money , pokemon->rarete);
    //Impossible d'acheter si :
    if( joueur->alive==false || joueur->money < pokemon->rarete || nbpkm >= 10){
        printf("Impossible d'effectuer l'achat de %s",pokemon->name);
    }
    else{
        printf("Achat en cours...\n");
        joueur->money-=pokemon->rarete;
        carte->click=1;
        joueur->team[nbpkm]=*pokemon;
    }
}




plaqueStat CreerGraphStats(SDL_Renderer* renderer, SDL_Window* window, player_t* player , int x , int y , int width_plaque , int hight_plaque){
    // Remet la taille de ton carré a la taille maximale


    plaqueStat plaque;
    // Charger une police de caractères
    TTF_Font* font = TTF_OpenFont("ressources/font/Pokemon_Classic.ttf", 12);
    if (font == NULL) {
        // Gestion de l'erreur de chargement de la police
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
    }

    SDL_Color gris = {50, 50, 50}; // Couleur texte

    // Créer une surface de texte
    SDL_Surface* nameS = TTF_RenderText_Solid(font, player->nom, gris);
    if (nameS == NULL) {
        // Gestion de l'erreur de création de la surface de texte
        printf("Erreur de création de la surface de texte : %s\n", TTF_GetError());
    }
       
    char* niveau=int_to_string(player->niveau);
    SDL_Surface* lvlS = TTF_RenderText_Solid(font, niveau, gris);
    if (lvlS == NULL) {
        // Gestion de l'erreur de création de la surface de texte
        printf("Erreur de création de la surface de texte : %s\n", TTF_GetError());
    }


    // Chargement de l'image
    SDL_Surface* plaqueS = IMG_Load("ressources/img/plaquestats.png"); 
    if (!plaqueS) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
    }

    //Creation des rectangles d'emplacement
    int  w = width_plaque;
    int  h = hight_plaque;

    SDL_Rect temp0={x,y,w,h};
    printf("x : %d ,y %d ,w %d ,h %d\n\n ", x,y,w,h);
    SDL_Rect temptxt={temp0.x + (temp0.w * 0.02),temp0.y + (temp0.h * 0.19), temp0.w * 0.84 ,  (temp0.h * 0.28) };
    SDL_Rect tempniv={temp0.x + (temp0.w * 0.75),temp0.y + (temp0.h * 0.55), temp0.w * 0.167 , (temp0.h * 0.265) };
    SDL_Rect temphp={temp0.x +  (temp0.w * 0.17),temp0.y + (temp0.h * 0.633),temp0.w * 0.54 ,  (temp0.h * 0.105) };
    temphp.w=temp0.w * 0.54 ;
    SDL_Rect tempxp={temp0.x +  (temp0.w * 0.06),temp0.y + (temp0.h * 0.87), temp0.w * 0.77 ,  (temp0.h * 0.08) };

    /*calcul dans la dimension de la bar de HP*/
    int cpt_hp=100;
    while(cpt_hp != player->hp){
        cpt_hp--;
    }
    temphp.w=(temphp.w  * cpt_hp) / 100;

    

    plaque.rectDest=temp0;
    plaque.rectTexte=temptxt;
    plaque.rectNiv=tempniv;
    plaque.rectHp=temphp;
    plaque.rectXp=tempxp;

    // Création d'une texture à partir de l'image
    plaque.plaqueT = SDL_CreateTextureFromSurface(renderer, plaqueS);
    SDL_FreeSurface(plaqueS); // Libération de la surface chargée

    if (!plaque.plaqueT) {
        SDL_Log("Erreur lors de la création de la texture : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
    }

    // Créer une texture à partir de la surface de texte
    plaque.nameT = SDL_CreateTextureFromSurface(renderer, nameS);
    if (plaque.nameT == NULL) {
    // Gestion de l'erreur de création de la texture
        printf("Erreur de création de la texture de texte : %s\n", SDL_GetError());
    }


    // Récupérer la hauteur et la largeur de la surface de texte
    int texteLargeur, texteHauteur;
    SDL_QueryTexture(plaque.nameT, NULL, NULL, &texteLargeur, &texteHauteur);
    //calcul en fonction des données
    float ratioHauteur = (float)temp0.h * 0.28 / texteHauteur;
    float ratioLargeur = (float)temp0.w * 0.84 / texteLargeur;
    float ratioMin = fmin(ratioHauteur, ratioLargeur);
    int textureLargeur = texteLargeur * ratioMin;
    int textureHauteur = texteHauteur * ratioMin;
    //redimension du rectangle
    plaque.rectTexte.x= temptxt.x;
    plaque.rectTexte.y= temptxt.y;
    plaque.rectTexte.w= textureLargeur;
    plaque.rectTexte.h= textureHauteur;

    
    // Créer une texture à partir de la surface de texte
    plaque.lvlT = SDL_CreateTextureFromSurface(renderer, lvlS);
    if (plaque.lvlT == NULL) {
    // Gestion de l'erreur de création de la texture
        printf("Erreur de création de la texture de texte : %s\n", SDL_GetError());
    }
    
    // Récupérer la hauteur et la largeur de la surface de texte
    texteLargeur, texteHauteur;
    SDL_QueryTexture(plaque.lvlT, NULL, NULL, &texteLargeur, &texteHauteur);
    //calcul en fonction des données
    ratioHauteur = (float)temp0.h * 0.28 / texteHauteur;
    ratioLargeur = (float)temp0.w * 0.84 / texteLargeur;
    ratioMin = fmin(ratioHauteur, ratioLargeur);
    textureLargeur = texteLargeur * ratioMin;
    textureHauteur = texteHauteur * ratioMin;
    //redimension du rectangle
    plaque.rectNiv.x= tempniv.x;
    plaque.rectNiv.y= tempniv.y;
    plaque.rectNiv.w= textureLargeur;
    plaque.rectNiv.h= textureHauteur;
    
    return plaque;
}

void AfficherGraphStats(SDL_Window* window, SDL_Renderer* renderer, plaqueStat plaque ,player_t* player){

    // Affichage de la texture à l'écran
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &plaque.rectHp);

    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &plaque.rectXp);

    SDL_RenderCopy(renderer, plaque.plaqueT, NULL, &plaque.rectDest);
    SDL_RenderCopy(renderer, plaque.nameT , NULL, &plaque.rectTexte);
    SDL_RenderCopy(renderer, plaque.lvlT, NULL, &plaque.rectNiv);
}
