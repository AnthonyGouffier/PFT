#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int arc, char* argv[]){
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d !\n",nb.major,nb.minor,nb.patch);
    return 0;
}

// gcc monprog.c -o output(.exe) -I include -L lib -lmingw32 -lSDL2main -lSDL2