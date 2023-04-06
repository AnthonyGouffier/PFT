/**
 * @file argent.c
 * @author Gérome vivien
 * @brief fonction qui calcul le nombre d'or que le joueur vas récupérer et calcul aussi les intérets
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commun.h"

int money(int tours,player_t player){

        if(tours<5){
            player.money+=tours;
        }else{
            player.money+=5;
        }



        if(player.money>=10 && player.money<20){
            player.interest=1;
        }else if(player.money>=20 && player.money<30){
            player.interest=2
        }else if(player.money>=30 && player.money<40){
            player.interest=3;
        }else if(player.money>=40 && player.money<50){
            player.interest=4;
        }else{
            player.interest=5;
        }

    player.money+=player.interest;

}