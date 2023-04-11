#include "combats.h"



/**
 * @brief tier de degat pour joueur
 * 
 */
int tier_damage_P[3][5] = {   //tier de damage a infliger au joueur
  {1,1,1,2,3},
  {2,2,2,3,4},
  {3,3,3,5,8}
};




int valides(int x,int y){
  if(x<0 || (N-1)<=x){
    return 0;
  }else if(y<0 || (N-1)<=x){
    return 0;
  }else{
    return 1;
  }
}

// calcul de degats 
int degats_subi_pkm(int hp,int armor,int attaque){
   int  deg = attaque-((armor*attaque)/100);
   hp -= deg;
   return hp;
}

int est_mort_pkm(int hp){
   if(hp<0){
    return 0;
   }
   return 1;
}


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

void deplacement_pok(pokemon_t * mat[N][N],pos_t pos,pos_t newpos){
    int i=newpos.x,j=newpos.y;
    int x=pos.x,y=pos.y;
      mat[i][j]=mat[x][y];
     // mat[i][j]=initialiserPkm(mat[i][j]);
      pos.x=newpos.x;
      pos.y=newpos.y;
}




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


int recuperehp(pokemon_t * mat[N][N],int x,int y){
  int hp;
  mat[x][y]->pv=hp;
  return hp;
} 


void affiche_test(pokemon_t * automate[N][N]){
  printf("\n");
  int i,j;

  printf("\n");
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++) {
      if(automate[i][j]->dresseur==enemi){
        printf(" E ");
      }else if(automate[i][j]->dresseur==pok){
        printf(" P ");
      }else{
        printf(" _ ");
      }
    }
    printf("\n");
  }
}


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

void combat(pokemon_t * mat[N][N]){
  pos_t enemi_proche;
  pos_t mat_pos[N][N];
  pos_t deplacement;

  for(int k=0;k<N;k++){
    for(int l=0;l<N;l++){
      mat_pos[k][l].x=k;
      mat_pos[k][l].y=l;
    }
  }

  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      printf("%d %d %d \n ",mat[i][j]->alive,i,j);
      if(mat[i][j]->alive==1){
        enemi_proche=detecte_enemie_proche(mat,enemi_proche,mat[i][j]->dresseur);
        if(aporter(mat,mat[i][j]->range,i,j)){
          mat[enemi_proche.x][enemi_proche.y]->pv=degats_subi_pkm(mat[enemi_proche.x][enemi_proche.y]->pv,mat[i][j]->def,mat[i][j]->att);
        }else{
          mat_pos[i][j]=avance(mat,enemi_proche.x,enemi_proche.y,i,j);
        }
      }
    }
  }

  for(int i2=0;i2<N;i2++){
    for(int j2=0;j2<N;j2++){
      if(mat_pos[i2][j2].x!=i2 || mat_pos[i2][j2].y!=j2){
        deplacement.x=i2;
        deplacement.y=j2;
        deplacement_pok(mat,mat_pos[i2][j2],deplacement);
      }
    }
  }

  for(int i3=0;i3<N;i3++){
    for(int j3=0;j3<N;j3++){
      if(est_mort_pkm(mat[i3][j3]->pv)){
        mat[i3][j3]->alive=0;
      }
    }
  }

}

int main(){
  pokemon_t *  plateau[N][N];
  pokemon_t *  poke=createPkmDatabase(1);
  pokemon_t *  poke2=createPkmDatabase(1);
  pokemon_t * poke_save;
  poke->alive=1;
  poke2->alive=1;
  poke2->dresseur=1;
  poke->dresseur=2;

  for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            plateau[i][j] = malloc(sizeof(pokemon_t));
            plateau[i][j]=initialiserPkm(plateau[i][j]);
        }
    }

    plateau[1][1]=poke;
    plateau[4][4]=poke2;
    poke_save=poke;
    printPkm(*poke_save);

    while(1){
      affiche_test(plateau);
      combat(plateau);
      printf("fin \n");
      sleep(1);
    }
}




