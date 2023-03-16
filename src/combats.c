#include "stdio.h"
#include "stdlib.h"
#include "math.h"
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




void avance(pok_t mat[N][N],int xenemie,int yenemie,int posx,int posy){
  pos_t newpos;
  pos_t pos;
  pos.x=posx;
  pos.y=posy; 
  newpos.x=posx;
  newpos.y=posy; 
  if (posx < xenemie) {
    newpos.x += 1;
    deplacement_pok(mat, pos, newpos);
    pos = newpos;
  } else if (posx > xenemie) {
    newpos.x -= 1;
    deplacement_pok(mat, pos, newpos);
    pos = newpos;
  } else {
    if (posy < yenemie) {
      newpos.y += 1;
      deplacement_pok(mat, pos, newpos);
      pos = newpos;
    } else if (posy > yenemie) {
      newpos.y -= 1;
      deplacement_pok(mat, pos, newpos);
      pos = newpos;
    }
  }
}

pos_t detecte_enemie_proche(pos_t pos,pok_t mat[N][N],int equipe){
    int i,j;
    int plus_procheX=-1,plus_procheY=-1;
    double distance_min = INFINITY;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){       //parcours la matrice 
            if(mat[i][j].equipe!=equipe && mat[i][j].equipe!=0){   //Si il trouve un enemie
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

void affiche_stat(pok_t mat[N][N],pos_t pos){
  int i=pos.x,j=pos.y;
  printf("%d %d %d %d %d %d %d %d %d %d",mat[i][j].life
  ,mat[i][j].equipe
  ,mat[i][j].hp
  ,mat[i][j].attaque
  ,mat[i][j].armor
  ,mat[i][j].x
  ,mat[i][j].y
  ,mat[i][j].porter
  ,mat[i][j].evol
  ,mat[i][j].tier);

}

void affiche_tout(pok_t mat[N][N]){
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


int main(){

    pok_t mat[N][N];
    initialise(mat);
    pos_t test75;
    test75.x =7;
    test75.y =7; 
    affiche_stat(mat,test75);
    affiche_tout(mat);
    mat[5][5].equipe=pok;
    mat[5][5].hp=50;
    mat[5][5].attaque=9;
    mat[5][5].armor=30;
    mat[5][5].x=5;
    mat[5][5].y=5;
    mat[5][5].porter=2;
    mat[5][5].evol=1;
    mat[5][5].tier=2;
    mat[5][5].life=1;

    mat[1][1].equipe=enemi;
    mat[1][1].hp=50;
    mat[1][1].attaque=9;  
    mat[1][1].armor=30;
    mat[1][1].x=1;
    mat[1][1].y=1;
    mat[1][1].porter=2;
    mat[1][1].evol=1;
    mat[1][1].tier=2;
    mat[1][1].life=1;

    PL_t player1;
    PL_t player2;
    player1.hp=100;
    player2.hp=100;
    player1.level=5;
    player2.level=5;

    pos_t enemi1;
    pos_t pok1;
    pos_t enemi_proche;
    pos_t testdep;
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
            enemi_proche.x=i;
            enemi_proche.y=j;
            printf("\n %d %d ",enemi_proche.y,enemi_proche.x);
            enemi_proche=detecte_enemie_proche(enemi_proche,mat,mat[i][j].equipe);

            printf("\n %d %d ",enemi_proche.y,enemi_proche.x);
            if(aporter(mat,mat[i][j].porter,i,j,enemi_proche)){
              printf("aporter");
              mat[i][j].hp=degats_subi_pkm(mat[i][j].hp,mat[i][j].armor,mat[i][j].attaque);
            }else{
              printf("avance");
              avance(mat,i,j,enemi_proche.x,enemi_proche.y);
              testdep.x=i;
              testdep.y=j;
              affiche_stat(mat,testdep);
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
    return 0;
}