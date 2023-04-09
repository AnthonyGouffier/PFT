#include "stdio.h"
#include "joueur.h"


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


void createPlayer(player_t* joueur){
    printf("Veuillez saisir votre nom : ");
    scanf("%s", joueur->nom);

    joueur->id = 0;
    
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

