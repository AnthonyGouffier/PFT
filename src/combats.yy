#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#define pok 1
#define enemi 2
#define N 7

typedef struct pos_s{
  int y;
  int x;
}pos_t;

typedef struct PL_s{
  int hp;
  int level;
}PL_t;

typedef struct pok_s{
  int y;
  int x;
  int hp;
  int attaque;
  int armor;
  int life;
  int equipe;
  int porter;
  int tier;
  int evol;
}pok_t;


int tier_damage[3][5] = {   //tier de damage a infliger au joueur
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
   return hp-=attaque*(100/(armor+100));
}


int aporter(pok_t mat[N][N],int porter,int xpos,int ypos,pos_t enemipos){
  int i,j;
  printf("ici ap");
  for(i=(xpos-porter);i<=(xpos+porter);i++){
    for(j=(ypos-porter);j<=(ypos+porter);j++){
      if(enemipos.y==ypos && enemipos.x==xpos){
        return 1;
      }
    }
  }
  return 0;
}


void effacer(pok_t mat[N][N],pos_t pos){
      int i=pos.x,j=pos.y;
      mat[i][j].life=-1;
      mat[i][j].equipe=0;
      mat[i][j].hp=0;
      mat[i][j].attaque=0;
      mat[i][j].armor=0;
      mat[i][j].x=i;
      mat[i][j].y=j;
      mat[i][j].porter=0;
      mat[i][j].evol=0;
      mat[i][j].tier=0;
}



void deplacement_pok(pok_t mat[N][N],pos_t pos,pos_t newpos){
      int i=newpos.x,j=newpos.y;
      int x=pos.x,y=pos.y;
      mat[i][j].life=mat[x][y].life;
      mat[i][j].equipe=mat[x][y].equipe;
      mat[i][j].hp=mat[x][y].hp;
      mat[i][j].attaque=mat[x][y].attaque;
      mat[i][j].armor=mat[x][y].armor;
      mat[i][j].x=newpos.x;
      mat[i][j].y=newpos.y;
      mat[i][j].porter=mat[x][y].porter;
      mat[i][j].evol=mat[x][y].evol;
      mat[i][j].tier=mat[x][y].tier;
      effacer(mat,pos);

}


pos_t detecte_enemie_proche(pos_t pos,pok_t mat[N][N]){
    int i,j;
    int plus_procheX=N,plus_procheY=N;
    for(i=0;i<=N;i++){
        for(j=0;j<=N;j++){       //parcous la matrice
            if(mat[i][j].equipe==enemi){   //Si il trouve un enemie
                //if(sqrt((i-pos.y)*(i-pos.y) + (j-pos.x)*(j-pos.x)) < sqrt((plus_procheX-pos.y)*(plus_procheX-pos.y) + (plus_procheY-pos.x)*(plus_procheY-pos.x))){
                plus_procheX=j;
                plus_procheY=i;
              }
            }
        }
    }
    printf("%d",plus_procheY);
    printf("%d",plus_procheX);
    pos.y=plus_procheY;
    pos.x=plus_procheX;
    printf("%d %d ",pos.y,pos.x);
    return pos;
}

void avance(pok_t mat[N][N],int xenemie,int yenemie,int posx,int posy){
  pos_t newpos;
  pos_t pos;
  pos.x=posx;
  pos.y=posy;
  newpos.x=posx;
  newpos.y=posy;
  if(posx<xenemie){
    printf("ici 1");
    newpos.x+=1;
    deplacement_pok(mat,pos,newpos);
  }else if(posx>xenemie){
    printf("ici 2");
    newpos.y-=1;
    deplacement_pok(mat,pos,newpos);
    printf("-1 x");
  }
  else{
    if(posy<yenemie){
      printf("ici");
      newpos.y+=1;
      deplacement_pok(mat,pos,newpos);
        printf("+y");
    }
    else if(posy>yenemie){
        printf("ici");
        newpos.y-=1;
        deplacement_pok(mat,pos,newpos);
        printf("y-");
    }
  }
}



int recupere_valeur(int row, int col) {
    FILE * fiche;
    int value;

    fiche = fopen("infoequipe.txt", "r");
    if (fiche == NULL) {
        printf("Error\n");
        return -1;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fscanf(fiche, "%d", &value);
        }
    }

    fclose(fiche);

    return value;
}


int dmg_player(pok_t mat[N][N],int stage,int hp){
  int dmg=0;
  int i,j;
  for(i=0; i<N; i++){
    for(j=0;j<N;j++){
      if(mat[i][j].equipe==enemi && mat[i][j].life==1){
        dmg+=tier_damage[mat[i][j].evol][mat[i][j].tier];
      }
    }
  }
  dmg+=stage;
  return (hp-dmg);
}


int recuperehp(pok_t mat[N][N],int x,int y){
  int hp;
  mat[x][y].hp=hp;
  return hp;
}


void affiche_test(pok_t automate[N][N]){
  printf("\n");
  int i,j;

  printf("\n");
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++) {
      if(automate[i][j].equipe==enemi){
        printf(" E ");
      }else if(automate[i][j].equipe==pok){
        printf(" P ");
      }else{
        printf(" _ ");
      }
    }
    printf("\n");
  }
}

void initialise(pok_t mat[N][N]){
  int i,j;
  for (i=0; i<N; i++) {
    for(j=0;j<N;j++) {
      mat[i][j].life=-1;
      mat[i][j].equipe=0;
      mat[i][j].hp=0;
      mat[i][j].attaque=0;
      mat[i][j].armor=0;
      mat[i][j].x=i;
      mat[i][j].y=j;
      mat[i][j].porter=0;
      mat[i][j].evol=0;
      mat[i][j].tier=0;
    }
  }
}



/*int main(){

    pok_t mat[N][N];
    initialise(mat);

    mat[5][2].equipe=pok;
    mat[5][2].hp=50;
    mat[5][2].attaque=9;
    mat[5][2].armor=30;
    mat[5][2].x=5;
    mat[5][2].y=2;
    mat[5][2].porter=2;
    mat[5][2].evol=1;
    mat[5][2].tier=2;
    mat[5][2].life=1;

    mat[0][0].equipe=enemi;
    mat[0][0].hp=50;
    mat[0][0].attaque=9;
    mat[0][0].armor=30;
    mat[0][0].x=0;
    mat[0][0].y=0;
    mat[0][0].porter=2;
    mat[0][0].evol=1;
    mat[0][0].tier=2;
    mat[0][0].life=2;

    PL_t player1;
    PL_t player2;
    player1.hp=100;
    player2.hp=100;
    player1.level=5;
    player2.level=5;

    pos_t enemi1;
    pos_t pok1;
    pos_t enemi_proche;

    enemi1.x =0;
    enemi1.y =0;
    pok1.x =5;
    pok1.y =2;
    int cpt = player1.level;
    int k,j,i,fin=0;


    affiche_test(mat);      //sauv de base + de debut de phase



    for(k=0;(k<20 || fin==1);k++){    //timer de 20 coup ou s arrete a fin
      printf("Temp=%d \n ",k);
      for(i=0;i<N; i++){
        for(j=0;j<N;j++){
          if(mat[i][j].life==1){
            printf("ici");
            enemi_proche.x=i;
            enemi_proche.y=j;
            enemi_proche=detecte_enemie_proche(enemi_proche,mat);
            if(aporter(mat,mat[i][j].porter,i,j,enemi_proche)){
              mat[i][j].hp=degats_subi_pkm(mat[i][j].hp,mat[i][j].armor,mat[i][j].attaque);
            }else{
              avance(mat,i,j,enemi_proche.x,enemi_proche.y);
            }
          }
        }
      }
      for(i=0; i<N; i++){
        for(j=0;j<N;j++){
          if(mat[i][j].hp<=0 && mat[i][j].equipe==pok){
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

    printf("fini");

}*/
