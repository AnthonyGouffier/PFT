#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


/*
CE FICHIER CONTIENT DES FONCTION POUR UTILISER LA SDL PLUS RAPIDEMENT
*/

extern
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


extern
SDLcheck(){
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d !\n",nb.major,nb.minor,nb.patch);
    return 0;
}

// gcc monprog.c -o output(.exe) -I include -L lib -lmingw32 -lSDL2main -lSDL2