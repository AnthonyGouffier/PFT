#include "stdio.h"
#include "carte.h"
#include "joueur.h"

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
