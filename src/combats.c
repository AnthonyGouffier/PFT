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


int aporter(pok_t mat[N][N],int porter,int xpos,int ypos){
  int j,i;
  for(i=(xpos-porter);i<=(xpos+porter);i++){
    for(j=(ypos-porter);j<=(ypos+porter);j++){
      if(valides(i,j)){
        if(mat[i][j].life==1 && mat[i][j].equipe!=mat[xpos][ypos].equipe){
        return 1; 
        }
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
      pos.x=newpos.x;
      pos.y=newpos.y;
}




pos_t avance(pok_t mat[N][N],int xenemie,int yenemie,int posx,int posy){
  pos_t newpos;
  pos_t pos;
  pos.x=posx;
  pos.y=posy; 
  newpos.x=posx;
  newpos.y=posy; 
  if (posx < xenemie && valides((newpos.x+1),newpos.y)){
    newpos.x += 1;
    return newpos;
  } else if (posx > xenemie && valides((newpos.x-1),newpos.y)){
    newpos.x -= 1;
    return newpos;
  } else if(posy < yenemie && valides(newpos.x,(newpos.y+1))){ 
      newpos.y += 1;
      return newpos;
  }else if(posy > yenemie && valides(newpos.x,(newpos.y-1))){
      newpos.y -= 1;
      return newpos;
  }
  printf("ne peut avancer");
  return newpos;
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
  printf(" \n ");

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
    int g1=0,g2=0;
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
    int h2=0,h1=1;
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
    */

    /*
    affiche_test(mat);
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
            if(aporter(mat,mat[i][j].porter,i,j)){
              printf("aporter");
              printf(" \n hp = %d",mat[i][j].hp);
              mat[i][j].hp=degats_subi_pkm(mat[i][j].hp,mat[i][j].armor,mat[i][j].attaque);
              printf(" \n hp = %d",mat[i][j].hp);
            }else{
              printf("avance");mat[4][4].x=4;
              mat[4][4].y=4;
              deplacement1.x=i;
              deplacement1.y=j;
              deplacement=avance(mat,i,j,enemi_proche.x,enemi_proche.y);
              deplacement_pok(mat,deplacement1,deplacement);
            }
          }
        }
      }
      for(i=0; i<N; i++){
        for(j=0;j<N;j++){
          if(mat[i][j].hp<=0 && mat[i][j].equipe==pok){
            printf("OK");
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
    */
    




    printf("fini");
    return 0;
}