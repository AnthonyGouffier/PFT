#include "commun.h"
#include "entites.h"

int tailleNiv1=6;
int tailleNiv2=5;
int tailleNiv3=4;
int tailleNiv4=3;
int tailleNiv5=2;

void auto_fill_pkm_stats(pokemon_t* pokemon,int taille){
  int indRar;
  do{
    printf("Saisir rareté (gris = 1 , vert  = 2 , bleu = 3 , violet = 4 or = 5");scanf("%d",&indRar);
  }
  while (indRar < 0 || indRar > 5);
  for (int j = 0 ; j < taille ; j++){
    (pokemon+j)->pv=(pokemon+j)->pv_max;
    (pokemon+j)->range=1;
    (pokemon+j)->stade=1;
    (pokemon+j)->alive=0;
    (pokemon+j)->dresseur=0;
    (pokemon+j)->img=NULL;
    (pokemon+j)->x=0 , (pokemon+j)->y=0;
    (pokemon+j)->rarete=indRar;
  }
}

char* capitalize(char *str) {
    char* new_str = strdup(str);
    new_str[0] = toupper(new_str[0]);
    return new_str;
}

/*Permet de créer un tableau de Pokémon avec les stats par défault*/
pokemon_t * createPkmDatabase(int taille){
  printf("taille %d\n",taille);
  char nomRecherche[52];
  char saisie[52];
  int i = 0 ;
  pokemon_t *tableau=malloc(sizeof(pokemon_t)*taille);        /* alloc taille tableau par rapport au nombre de Pokemon */
  FILE * ptrFich = fopen("data.csv","r"); 
  if (ptrFich == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
  }
  while(i<taille){
    ptrFich = fopen("data.csv","r");
    printf("Saisir le nom du pokemon à rechercher : ");
    /*saisie nom pokemon*/
    fgets(saisie, sizeof(saisie), stdin);
    saisie[strcspn(saisie, "\n")] = '\0'; // Remplace '\n' par '\0'
    char *token = strtok(saisie, " "); // Divise la chaîne de caractères en plusieurs mots
    strcpy(nomRecherche, capitalize(token)); // Stocke le premier mot dans la variable nomRecherche
    while (token != NULL) {
        token = strtok(NULL, " "); // Récupère le mot suivant
        if (token != NULL) {
            strcat(nomRecherche, " ");
            strcat(nomRecherche, capitalize(token)); // Ajoute le mot suivant à la variable nomRecherche
        }
    }
                  /*recherche pokemon*/ 
    fscanf(ptrFich,"%d;%[^;];%[^;];%d;%d;%f;%f;%f;%f;%f;",&(tableau+i)->id,(tableau+i)->name,(tableau+i)->classe,&(tableau+i)->total,&(tableau+i)->pv_max,&(tableau+i)->att,&(tableau+i)->def,&(tableau+i)->attspe,&(tableau+i)->defspe,&(tableau+i)->spd);
    while((strcmp(nomRecherche, tableau[i].name) != 0) && (!feof(ptrFich)) ){       
      //printf("Recherche en cours : %s %s\n",nomRecherche,tableau[i].name); 
      fscanf(ptrFich,"%d;%[^;];%[^;];%d;%d;%f;%f;%f;%f;%f;",&(tableau+i)->id,(tableau+i)->name,(tableau+i)->classe,&(tableau+i)->total,&(tableau+i)->pv_max,&(tableau+i)->att,&(tableau+i)->def,&(tableau+i)->attspe,&(tableau+i)->defspe,&(tableau+i)->spd);
      //printf("Valeur de i  : %d\n",i);        
    }
    if(feof(ptrFich)){
      printf("Erreur lors de la saisie du nom du Pokémon, veuillez réésayer\n");
      i--;
    }
    i++;
    rewind(ptrFich);
  }
  fclose(ptrFich);
  auto_fill_pkm_stats(tableau,taille);

  system("cls");
  system("clear");

  printf("\a liste créé\f");
  return tableau;
}

void printPkm(pokemon_t pokemon){
  printf("Nom : %s (id:%d) \nType : %s\nTotal %d\n PV max %d\n PV %d\n Attaque %3.f\n Defense %3.f\n Attaque Speciale %3.f\n Defense Speciale %3.f\n Vitesse %3.f\n portee %d\n Rarete %d\n ",pokemon.name,pokemon.id,pokemon.classe,pokemon.total,pokemon.pv_max,pokemon.pv,pokemon.att,pokemon.def,pokemon.attspe,pokemon.defspe,pokemon.spd,pokemon.range,pokemon.rarete);
  printf("Ce Pokemon appartient a joueur %d\n", pokemon.dresseur);
  printf("Status : %d\n Stade d'évolution : %d\n",pokemon.alive,pokemon.stade);
  printf("Position actuelle :(%d,%d)\n", pokemon.x,pokemon.y);
  printf("\n");
}

void affichertableau(pokemon_t *tableau, int taille){
  // Vider le flux d'entrée
  while (getchar() != '\n');

  for (int i = 0 ; i < taille ; i++){
    printf("Pokemon numero %d\n ",i+1);
    printf("Nom : %s  ID :  %d \n",(tableau+i)->name,(tableau+i)->id);
    printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar();
  }
}

void afficherEquipe(pokemon_t *equipe,int taille){
  //taille=sizeof((equipe)-1);
  for (int i = 0; i < taille; i++)
  {
    printPkm(equipe[i]);
  }
  
}

int main(){
  pokemon_t *niv1database=createPkmDatabase(tailleNiv1);
 // pokemon_t *niv2database=createPkmDatabase(tailleNiv2);
 // pokemon_t *niv3database=createPkmDatabase(tailleNiv3);
 // pokemon_t *niv4database=createPkmDatabase(tailleNiv4);
 // pokemon_t *niv5database=createPkmDatabase(tailleNiv5);
  afficherEquipe(niv1database,tailleNiv1);
  printf("Le code fonctionne correctement !\n");
 // afficherEquipe(niv2database,tailleNiv2);
 // afficherEquipe(niv3database,tailleNiv3);
 // afficherEquipe(niv4database,tailleNiv4);
 // afficherEquipe(niv5database,tailleNiv5);
  pokemon_t *database[(6*29)+(5*22)+(4*16)+(3*12)+(2*10)]; 
  
for(int cpt=0 ; cpt<tailleNiv1;cpt++){
  for (int copie=0;copie<29;copie++){
    *database[cpt+copie]=niv1database[cpt];
  }
}
affichertableau(database,tailleNiv1*29);
}
