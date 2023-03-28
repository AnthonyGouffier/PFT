#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
// gcc monprog.c -o output(.exe) -I include -L lib -lmingw32 -lSDL2main -lSDL2

int main(int arc, char* argv[]){
    SDL_Window* window=NULL;
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_VIDEO) != 0){
        SDL_Log("Erreur initialisation SDL : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    window=SDL_CreateWindow("Test SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,0);
   
    if (window==NULL){
        SDL_Log("Probleme creation fenetre : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Delay(5000);
    SDL_Quit();
    return EXIT_SUCCESS;
}