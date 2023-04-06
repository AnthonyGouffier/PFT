/**
 * @file combats.c
 * @author Gaumont Mael
 * @brief programme qui va permetre de faire combatre deux équipes de pokémon l'une contre l'autre
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "combats.h"



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


int aporter(pokemon_t mat[N][N],int porter,int xpos,int ypos){
  int j,i;
  for(i=(xpos-porter);i<=(xpos+porter);i++){
    for(j=(ypos-porter);j<=(ypos+porter);j++){
      if(valides(i,j)){
        if(mat[i][j].alive==1 && mat[i][j].dresseur!=mat[xpos][ypos].dresseur){
        return 1; 
        }
      }
    }
  } 
  return 0;
}


void effacer(pokemon_t mat[N][N],pos_t pos){
      int i=pos.x,j=pos.y;
      mat[i][j].id=0;
      mat[i][j].alive=0;
      mat[i][j].dresseur=0;
      mat[i][j].pv=0;
      mat[i][j].pv_max=0;
      mat[i][j].total=0;
      mat[i][j].att=0;
      mat[i][j].def=0;
      mat[i][j].attspe=0;
      mat[i][j].defspe=0;
      mat[i][j].spd=0;
      mat[i][j].x=i;
      mat[i][j].y=j;
      mat[i][j].range=0;
      mat[i][j].stade=0;
      mat[i][j].rarete=0;
      mat[i][j].imgSurface=NULL;
} 



void deplacement_pok(pokemon_t mat[N][N],pos_t pos,pos_t newpos){
    int i=newpos.x,j=newpos.y;
    int x=pos.x,y=pos.y;
      mat[i][j]=mat[x][y];
      effacer(mat,pos);
      pos.x=newpos.x;
      pos.y=newpos.y;
}




pos_t avance(pokemon_t mat[N][N],int xenemie,int yenemie,int posx,int posy){
  pos_t newpos;
  pos_t pos;
  pos.x=posx;
  pos.y=posy; 
  newpos.x=posx;
  newpos.y=posy; 
  if (posx < xenemie && valides((newpos.x+1),newpos.y ) && mat[newpos.x+1][newpos.y].alive!=1){
    newpos.x += 1;
    return newpos;
  } else if (posx > xenemie && valides((newpos.x-1),newpos.y) && mat[newpos.x-1][newpos.y].alive!=1){
    newpos.x -= 1;
    return newpos;
  } else if(posy < yenemie && valides(newpos.x,(newpos.y+1)) && mat[newpos.x][newpos.y+1].alive!=1){ 
      newpos.y += 1;
      return newpos;
  }else if(posy > yenemie && valides(newpos.x,(newpos.y-1)) && mat[newpos.x][newpos.y-1].alive!=1){
      newpos.y -= 1;
      return newpos;
  }
  printf("ne peut avancer");
  return newpos;
}

pos_t detecte_enemie_proche(pokemon_t mat[N][N],pos_t pos,int equipe){
    int i,j;
    int plus_procheX=-1,plus_procheY=-1;
    double distance_min = INFINITY;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){       //parcours la matrice 
            if(mat[i][j].dresseur!=equipe && mat[i][j].dresseur!=0){   //Si il trouve un enemie
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




int dmg_player(pokemon_t mat[N][N],int stage,int hp){
  int dmg=0;
  int i,j;
  for(i=0; i<N; i++){
    for(j=0;j<N;j++){
      if(mat[i][j].dresseur==enemi && mat[i][j].alive==1){
        dmg+=tier_damage[mat[i][j].stade][mat[i][j].rarete];
      }
    }
  }
  dmg+=stage;
  return (hp-dmg);
}


int recuperehp(pokemon_t mat[N][N],int x,int y){
  int hp;
  mat[x][y].pv=hp;
  return hp;
} 


void affiche_test(pokemon_t automate[N][N]){
  printf("\n");
  int i,j;

  printf("\n");
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++) {
      if(automate[i][j].dresseur==enemi){
        printf(" E ");
      }else if(automate[i][j].dresseur==pok){
        printf(" P ");
      }else{
        printf(" _ ");
      }
    }
    printf("\n");
  }
}


void affiche_stat(pokemon_t mat[N][N],pos_t pos){
  int i=pos.x,j=pos.y;
  printf("%d %d %d %f %f %d %d %d %d %d",mat[i][j].alive
  ,mat[i][j].dresseur
  ,mat[i][j].pv
  ,mat[i][j].att
  ,mat[i][j].def
  ,mat[i][j].x
  ,mat[i][j].y
  ,mat[i][j].range
  ,mat[i][j].stade
  ,mat[i][j].rarete);
  printf(" \n ");

}

void affiche_tout(pokemon_t mat[N][N]){
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

/*
int main(){

    pok_t mat[N][N];
    initialise(mat);
    int g1=2,g2=2;
    mat[g2][g1].equipe=pok;
    mat[g2][g1].hp=50;
    mat[g2][g1].attaque=20;
    mat[g2][g1].armor=5;
    mat[g2][g1].x=g2;
    mat[g2][g1].y=g1;
    mat[g2][g1].porter=2;
    mat[g2][g1].evol=1;
    mat[g2][g1].tier=2;
    mat[g2][g1].life=1;
    int h2=5,h1=5;
    mat[h2][h1].equipe=enemi;
    mat[h2][h1].hp=50;
    mat[h2][h1].attaque=20;  
    mat[h2][h1].armor=5;
    mat[h2][h1].x=h2;
    mat[h2][h1].y=h1;
    mat[h2][h1].porter=2;
    mat[h2][h1].evol=h1;
    mat[h2][h1].tier=2;
    mat[h2][h1].life=1;
    affiche_tout(mat);
    PL_t player1;
    PL_t player2;
    player1.hp=100;
    player2.hp=100;
    player1.level=5;
    player2.level=5;

    pos_t deplacement2;
    pos_t deplacement1;
    pos_t testdep;
    pos_t testdep2;
    pos_t enemi1;
    pos_t pok1;
    pos_t enemi_proche;
    enemi1.x =h2;
    enemi1.y =h1;

    pok1.x =g2;
    pok1.y =g1;
    int cpt = player1.level;
    int k,j,i,fin=0;


    /* //tour de terrain (marche)
    testdep=enemi1;
    affiche_test(mat);      //sauv de base + de debut de phase
    affiche_stat(mat,enemi1);
    for(int r=0;r<N;r++){
      for(int r2=0;r2<N;r2++){
        affiche_stat(mat,testdep);
        testdep2=testdep;
        testdep.x=r;
        testdep.y=r2;
        deplacement_pok(mat,testdep2,testdep);
        affiche_test(mat); 
        affiche_stat(mat,testdep);
      }
    }
    /*


    //test de porter (marche)
    int testpor;
    mat[0][2]=mat[h2][h1];
    mat[3][2]=mat[h2][h1];
    mat[1][5]=mat[g2][g1];
    affiche_test(mat);
    testpor=aporter(mat,mat[1][5].porter,1,5);
    printf("%d porter \n ",mat[1][5].porter);
    printf("%d porter \n ",testpor);

    */
    /*
                //test pour avance (marche)
    pos_t test8; 
    pos_t savepos;
    mat[0][2]=mat[h2][h1];
    mat[1][2]=mat[h2][h1];
    mat[6][6]=mat[g2][g1];
    test8.x=6;
    test8.y=6;
    for(int p=0;p<10;p++){
      affiche_test(mat);
      savepos=test8;
      test8=avance(mat,1,2,savepos.x,savepos.y);
      printf("x=%d y=%d \n ",test8.x,test8.y);
      printf("x=%d y=%d \n ",savepos.x,savepos.y);
      deplacement_pok(mat,savepos,test8);
    }
    */


    //test de dega a porter (marche)
  /*
    pos_t test9; 
    mat[4][5]=mat[h2][h1];
    mat[4][4]=mat[g2][g1];
    mat[4][4].x=4;
    mat[4][4].y=4;
    mat[4][5].x=4;
    mat[4][5].y=5;
    test9.x=4;
    test9.y=5;
    int newhp;
    affiche_stat(mat,test9);
    if(aporter(mat,mat[4][4].porter,4,5)==1){
      printf("c est bon \n ");
      newhp=degats_subi_pkm(mat[4][5].hp,mat[4][5].armor,mat[4][4].attaque);
      printf("deg = %d \n ",newhp);
      mat[4][5].hp=newhp;
      affiche_stat(mat,test9);
    }
    affiche_stat(mat,test9);
    affiche_test(mat);

    affiche_test(mat);
    for(k=0;(k<50 || fin==1);k++){    //timer de 20 coup ou s arrete a fin
      printf("Temp=%d \n ",k);
      for(i=0;i<N; i++){
        for(j=0;j<N;j++){
          if(mat[i][j].life==1){
              enemi_proche.x=i;
              enemi_proche.y=j;
              enemi_proche=detecte_enemie_proche(enemi_proche,mat,mat[i][j].equipe);
            if(aporter(mat,mat[i][j].porter,i,j)){
              mat[enemi_proche.x][enemi_proche.y].hp=degats_subi_pkm(mat[i][j].hp,mat[i][j].armor,mat[i][j].attaque);
            }else{
              deplacement1=avance(mat,enemi_proche.x,enemi_proche.y,i,j);
              deplacement2.x=i;
              deplacement2.y=j;
              if(deplacement1.x!=deplacement2.x || deplacement1.y!=deplacement2.y){
                deplacement_pok(mat,deplacement2,deplacement1);
              }
            }
          }
        }
      }
      for(i=0; i<N; i++){
        for(j=0;j<N;j++){
          if(mat[i][j].hp<=0 && mat[j][i].equipe>0){
            printf("mort");
            mat[i][j].life=0;
            cpt--;
          }
        }
      }
    if(cpt==0){
      fin=1;
    }
    affiche_test(mat);
    }
    affiche_tout(mat);
    




    printf("fini");
    return 0;
}

*/