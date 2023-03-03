#include "commun.h"
#include "entites.h"

void auto_fill_pkm_stats(pokemon_t* pokemon,int taille){
  int indRar;
  for (int j = 0 ; j < taille ; j++){
    (pokemon+j)->pv=(pokemon+j)->pv_max;
    (pokemon+j)->range=1;
    printf("Saisir Rarete (1 = Gris ,2 = Vert, 3 = Bleu, 4 = Violet ,5 = Or)"); scanf("%d",&indRar);
    (pokemon+j)->rarete=indRar;
    (pokemon+j)->stade=1;
    (pokemon+j)->alive=0;
    (pokemon+j)->dresseur=0;
    (pokemon+j)->img=NULL;
    (pokemon+j)->x=0 , (pokemon+j)->y=0;
  }
}

char* capitalize(char *str) {
    char* new_str = strdup(str);
    new_str[0] = toupper(new_str[0]);
    return new_str;
}

/*Permet de créer un tableau de Pokémon avec les stats par défault*/
pokemon_t * createPkmDatabase( int taille){
  //printf("taille %d\n",taille);
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
      printf("Recherche en cours : %s %s\n",nomRecherche,tableau[i].name);
      fscanf(ptrFich,"%d;%[^;];%[^;];%d;%d;%f;%f;%f;%f;%f;",&(tableau+i)->id,(tableau+i)->name,(tableau+i)->classe,&(tableau+i)->total,&(tableau+i)->pv_max,&(tableau+i)->att,&(tableau+i)->def,&(tableau+i)->attspe,&(tableau+i)->defspe,&(tableau+i)->spd);
      printf("Valeur de i  : %d\n",i);
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


/*int main(){
    int taille=5;
 // printf("Saisir taille : "); scanf("%d",&taille);
    printf("valeur de taille : %d\n ",taille);
    pokemon_t *database=createPkmDatabase(taille);
    printf("Affichage de tableau :\n");
    sleep(1);
    affichertableau(database,taille);
    pokemon_t bulbizarre=database[0];
    printPkm(bulbizarre);
}*/
