#include "combats.h"

/**
 * @brief tier de degat pour les degats des jouer 
 * 
 */
int tier_damage_P[3][5] = {   
  {1,1,1,2,3},
  {2,2,2,3,4},
  {3,3,3,5,8}
};



/**
 * @brief verifie les coordonner pour savoir si on se situe dans la matrice
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int valides(int x,int y){
  if(x<0 || (N-1)<=x){
    return 0;
  }else if(y<0 || (N-1)<=x){
    return 0;
  }else{
    return 1;
  }
}

/**
 * @brief calcule de degat en fonction d un enemie que doit recevoir un pokemon
 * 
 * @param hp 
 * @param armor 
 * @param attaque 
 * @return int 
 */
int degats_subi_pkm(int hp,int armor,int attaque){
   int  deg = (attaque-((armor*attaque)/100));
   hp -= deg;
   return hp;
}

int est_mort_pkm(int hp){
   if(hp<=0){
    return 0;
   }
   return 1;
}

/**
 * @brief verifie si il a un pokemon enemie a porter 
 * 
 * @param mat 
 * @param porter 
 * @param xpos 
 * @param ypos 
 * @return int 
 */
int aporter(pokemon_t * mat[N][N],int porter,int xpos,int ypos){
  int j,i;
  for(i=(xpos-porter);i<=(xpos+porter);i++){
    for(j=(ypos-porter);j<=(ypos+porter);j++){
      if(valides(i,j)){
        if(mat[i][j]->alive==1 && mat[i][j]->dresseur!=mat[xpos][ypos]->dresseur){
        return 1; 
        }
      }
    }
  } 
  return 0;
}

/**
 * @brief deplace un pokemon a des coordonner donner
 * 
 * @param mat 
 * @param pos 
 * @param newpos 
 */
void deplacement_pok(pokemon_t * mat[N][N],pos_t pos,pos_t newpos){
  if(pos.x != newpos.x || pos.y != newpos.y){
    *mat[newpos.x][newpos.y]=*mat[pos.x][pos.y];
    *mat[pos.x][pos.y]=initialiserPkm();
  }
  
}



/**
 * @brief avance d une case vers une position donner
 * 
 * @param mat 
 * @param xenemie 
 * @param yenemie 
 * @param posx 
 * @param posy 
 * @return pos_t 
 */
pos_t avance(pokemon_t * mat[N][N],int xenemie,int yenemie,int posx,int posy){
  pos_t newpos;
  pos_t pos;
  pos.x=posx;
  pos.y=posy; 
  newpos.x=posx;
  newpos.y=posy; 
  if (posx < xenemie && valides((newpos.x+1),newpos.y ) && mat[newpos.x+1][newpos.y]->alive!=1){
    newpos.x += 1;
    printf("déplacement\n");
    return newpos;
  } else if (posx > xenemie && valides((newpos.x-1),newpos.y) && mat[newpos.x-1][newpos.y]->alive!=1){
    newpos.x -= 1;
    printf("déplacement\n");
    return newpos;
  } else if(posy < yenemie && valides(newpos.x,(newpos.y+1)) && mat[newpos.x][newpos.y+1]->alive!=1){ 
      newpos.y += 1;
      printf("déplacement\n");
      return newpos;
  }else if(posy > yenemie && valides(newpos.x,(newpos.y-1)) && mat[newpos.x][newpos.y-1]->alive!=1){
      newpos.y -= 1;
      printf("déplacement\n ");
      return newpos;
  }
  printf("ne peut avancer");
  return newpos;
}

/**
 * @brief detecte l'enemie le plus prche d un pokemon donner
 * 
 * @param mat 
 * @param pos 
 * @param equipe 
 * @return pos_t 
 */
pos_t detecte_enemie_proche(pokemon_t * mat[N][N],pos_t pos,int equipe){
    int i,j;
    int plus_procheX=-1,plus_procheY=-1;
    double distance_min = INFINITY;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){       //parcours la matrice 
            if(mat[i][j]->dresseur!=equipe && mat[i][j]->dresseur!=0){   //Si il trouve un enemie
                double distance = sqrt(pow(i-pos.y, 2) + pow(j-pos.x, 2));
                if(distance < distance_min){
                    distance_min = distance;
                    plus_procheX = j;
                    plus_procheY = i;
                }
            }
        }
    }
    if(plus_procheX != -1 && plus_procheY != -1){
        pos.x = plus_procheX;
        pos.y = plus_procheY;
    }
    return pos;
}



/**
 * @brief calcule les degats que dois recevoir un joueur en 
 * fonction si il a fait une grosse ou petit defaite .le calcule se fait en fonction de 
 * la force des pokemon enemi encore en vie sur le terrain. 
 * 
 * @param mat 
 * @param stage 
 * @param hp 
 * @param equipe 
 * @return int 
 */
int dmg_player(pokemon_t * mat[N][N],int stage,int hp,int equipe){
  int dmg=0;
  int i,j;
  for(i=0; i<N; i++){
    for(j=0;j<N;j++){
      if(mat[i][j]->dresseur=!equipe && mat[i][j]->alive==1){
        dmg+=tier_damage_P[mat[i][j]->stade][mat[i][j]->rarete];
      }
    }
  }
  dmg+=stage;
  return (hp-dmg);
}

/**
 * @brief recupere les hp d un pokemon a un endroit preci
 * 
 * @param mat 
 * @param x 
 * @param y 
 * @return int 
 */
int recuperehp(pokemon_t * mat[N][N],int x,int y){
  int hp;
  mat[x][y]->pv=hp;
  return hp;
} 

/**
 * @brief affichage pour tester les combats
 * 
 * @param mat 
 */
void affiche_test(pokemon_t * automate[N][N]){
  printf("\n");
  int i,j;

  printf("\n");
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++) {
      if(automate[i][j]->dresseur==enemi && automate[i][j]->alive==1){
        printf(" E ");
      }else if(automate[i][j]->dresseur==pok  && automate[i][j]->alive==1){
        printf(" P ");
      }else{
        printf(" _ ");
      }
    }
    printf("\n");
  }
}

/**
 * @brief affiche tout les stat d un pokemon utile aux combats
 * 
 * @param mat 
 */
void affiche_stat(pokemon_t * mat[N][N],pos_t pos){
  int i=pos.x,j=pos.y;
  printf("%d %d %d %f %f %d %d %d %d %d",mat[i][j]->alive
  ,mat[i][j]->dresseur
  ,mat[i][j]->pv
  ,mat[i][j]->att
  ,mat[i][j]->def
  ,mat[i][j]->x
  ,mat[i][j]->y
  ,mat[i][j]->range
  ,mat[i][j]->stade
  ,mat[i][j]->rarete);
}

/**
 * @brief affiche tout les stat des pokemon utile aux combats
 * 
 * @param mat 
 */
void affiche_tout(pokemon_t * mat[N][N]){
  int i,j;
  pos_t pos;
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++){
      printf("\n");
      pos.x=i;
      pos.y=j;
      affiche_stat(mat,pos);
    }
  }
}

/**
 * @brief permet de fair un tour de combats cela veut dire que les entite
  sur le terrain en vie vont tous faire une action (attaque ou ce deplacer).
  permet aussi de suprimer les pokemons mort.
 * 
 * @param mat 
 */
void combat(pokemon_t * mat[N][N],int tour){
  pos_t enemi_proche;
  pos_t deplacement,deplacement2;




  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(mat[i][j]->alive==1){
        enemi_proche=detecte_enemie_proche(mat,enemi_proche,mat[i][j]->dresseur);
        if(aporter(mat,mat[i][j]->range,i,j)==1 && mat[i][j]->x==tour){
          mat[i][j]->x+=1;
          mat[enemi_proche.y][enemi_proche.x]->pv=degats_subi_pkm(mat[enemi_proche.y][enemi_proche.x]->pv,mat[enemi_proche.y][enemi_proche.x]->def,mat[i][j]->att);
          printPkm(*mat[i][j]);
        }else{
        if(mat[i][j]->x==tour){   
              mat[i][j]->x+=1;
              deplacement2=avance(mat,enemi_proche.y,enemi_proche.x,i,j);
              deplacement.x=i;
              deplacement.y=j;
              deplacement_pok(mat,deplacement,deplacement2);
           }
          }
        }
    }
   }



  for(int i3=0;i3<N;i3++){
    for(int j3=0;j3<N;j3++){
      if(est_mort_pkm(mat[i3][j3]->pv)==0 && mat[i3][j3]->id>0){
        mat[i3][j3]->alive=0;
      }
    }
  }

}

/**
 * @brief remet en vie les pokemon mort au combat et suprime les pokemon ennemie
 * 
 * @param mat 
 * @param equipe 
 */
void reset_plateau(pokemon_t * mat[N][N],int equipe){
  pokemon_t * poke;
  *poke=initialiserPkm();
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(mat[i][j]!=poke){
        if(mat[i][j]->dresseur==equipe){
          mat[i][j]->pv==mat[i][j]->pv_max;
        }else{
          mat[i][j]=poke;
        }
      }
    }
  }
}

/**
 * @brief test de combat
 * 
 * @return int 
 */
int main(){
  pokemon_t *  plateau[N][N];
  pokemon_t *  poke=createPkmDatabase(1,1);
  pokemon_t *  poke2=createPkmDatabase(1,1);
  pokemon_t *  poke3=createPkmDatabase(1,1);
  pokemon_t *  poke4=createPkmDatabase(1,1);
  pokemon_t * poke_save;
  poke->alive=1;
  poke2->alive=1;
  poke3->alive=1;
  poke4->alive=1;
  poke2->dresseur=2;
  poke->dresseur=2;
  poke3->dresseur=1;
  poke4->dresseur=1;


  int cpt=0;

  for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            plateau[i][j] = malloc(sizeof(pokemon_t));
            *plateau[i][j]=initialiserPkm();
        }
    }

    plateau[3][2]=poke4;
    plateau[6][4]=poke2;
    plateau[3][3]=poke3;
    plateau[6][3]=poke2;
    poke_save=poke;

    while(1){
      affiche_test(plateau);
      combat(plateau,cpt);
      printf("fin \n");
      sleep(1);
      cpt++;
    }
}




