

plaqueStat CreerGraphStats(SDL_Renderer* renderer, SDL_Window* window, player_t* player , int x , int y , int width_plaque , int hight_plaque){
    
    plaqueStat plaque;

    // Charger une police de caractères
    TTF_Font* font = TTF_OpenFont("ressources/font/Pokemon_Classic.ttf", 12);
    if (font == NULL) {
        // Gestion de l'erreur de chargement de la police
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
    }

    SDL_Color gris = {50, 50, 50}; // Couleur blanche

    // Créer une surface de texte
    SDL_Surface* nameS = TTF_RenderText_Solid(font, player->nom, gris);
    if (nameS == NULL) {
        // Gestion de l'erreur de création de la surface de texte
        printf("Erreur de création de la surface de texte : %s\n", TTF_GetError());
    }
       
    char* niveau=int_to_string(player->niveau);
    SDL_Surface* lvlS = TTF_RenderText_Solid(font, niveau, gris);
    if (lvlS == NULL) {
        // Gestion de l'erreur de création de la surface de texte
        printf("Erreur de création de la surface de texte : %s\n", TTF_GetError());
    }


    // Chargement de l'image
    SDL_Surface* plaqueS = IMG_Load("ressources/img/plaquestats.png"); 
    if (!plaqueS) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
        return;
    }

    //Creation des rectangles d'emplacement
    int const x = 0; 
    int const y = 120;
    int const w = width_plaque;
    int const h = hight_plaque;
    SDL_Rect temp0={x,y,w,h};
    SDL_Rect temptxt={temp0.x + (temp0.w * 0.02),temp0.y + (temp0.h * 0.19), temp0.w * 0.84 ,  (temp0.y * 0.28) };
    SDL_Rect tempniv={temp0.x + (temp0.w * 0.75),temp0.y + (temp0.h * 0.55), temp0.w * 0.167 , (temp0.y * 0.265) };
    SDL_Rect temphp={temp0.x +  (temp0.w * 0.17),temp0.y + (temp0.h * 0.633),temp0.w * 0.53 ,  (temp0.y * 0.105) };
    SDL_Rect tempxp={temp0.x +  (temp0.w * 0.06),temp0.y + (temp0.h * 0.87), temp0.w * 0.77 ,  (temp0.y * 0.07) };


    plaque.rectDest=temp0;
    plaque.rectTexte=temptxt;
    plaque.rectNiv=tempniv;
    plaque.rectHp=temphp;
    plaque.rectXp=tempxp;

    // Création d'une texture à partir de l'image
    plaque.plaqueT = SDL_CreateTextureFromSurface(renderer, plaqueS);
    SDL_FreeSurface(plaqueS); // Libération de la surface chargée

    if (!plaque.plaqueT) {
        SDL_Log("Erreur lors de la création de la texture : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
        return;
    }

    // Créer une texture à partir de la surface de texte
    plaque.nameT = SDL_CreateTextureFromSurface(renderer, nameS);
    if (plaque.nameT == NULL) {
    // Gestion de l'erreur de création de la texture
        printf("Erreur de création de la texture de texte : %s\n", SDL_GetError());
    }


    // Récupérer la hauteur et la largeur de la surface de texte
    int texteLargeur, texteHauteur;
    SDL_QueryTexture(plaque.nameT, NULL, NULL, &texteLargeur, &texteHauteur);
    //calcul en fonction des données
    float ratioHauteur = (float)temp0.h * 0.28 / texteHauteur;
    float ratioLargeur = (float)temp0.w * 0.84 / texteLargeur;
    float ratioMin = fmin(ratioHauteur, ratioLargeur);
    int textureLargeur = texteLargeur * ratioMin;
    int textureHauteur = texteHauteur * ratioMin;
    //redimension du rectangle
    plaque.rectTexte.x= temptxt.x;
    plaque.rectTexte.y= temptxt.y;
    plaque.rectTexte.w= textureLargeur;
    plaque.rectTexte.h= textureHauteur;

    
    // Créer une texture à partir de la surface de texte
    plaque.lvlT = SDL_CreateTextureFromSurface(renderer, lvlS);
    if (plaque.lvlT == NULL) {
    // Gestion de l'erreur de création de la texture
        printf("Erreur de création de la texture de texte : %s\n", SDL_GetError());
    }
    
    // Récupérer la hauteur et la largeur de la surface de texte
    texteLargeur, texteHauteur;
    SDL_QueryTexture(plaque.lvlT, NULL, NULL, &texteLargeur, &texteHauteur);
    //calcul en fonction des données
    ratioHauteur = (float)temp0.h * 0.28 / texteHauteur;
    ratioLargeur = (float)temp0.w * 0.84 / texteLargeur;
    ratioMin = fmin(ratioHauteur, ratioLargeur);
    textureLargeur = texteLargeur * ratioMin;
    textureHauteur = texteHauteur * ratioMin;
    //redimension du rectangle
    plaque.rectNiv.x= tempniv.x;
    plaque.rectNiv.y= tempniv.y;
    plaque.rectNiv.w= textureLargeur;
    plaque.rectNiv.h= textureHauteur;
    
    return plaque;
}

void AfficherGraphStats(SDL_Window* window, SDL_Renderer* renderer, plaqueStat plaque ,player_t* player){

    // Affichage de la texture à l'écran
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &plaque.rectHp);

    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &plaque.rectXp);

    SDL_RenderCopy(renderer, plaque.plaqueT, NULL, &plaque.rectDest);
    SDL_RenderCopy(renderer, plaque.nameT , NULL, &plaque.rectTexte);
    SDL_RenderCopy(renderer, plaque.lvlT, NULL, &plaque.rectNiv);
}
