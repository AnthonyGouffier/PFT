#include <SDL2/SDL.h>
#include <SLD2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    
    /*initialisation de la SDL*/
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) ){
        fprintf(stderr,"SDL Erreur : %s\n",SDL_GetError());
        goto Quit;
    }
    
    /*Creation d'une fenetre*/
    SDL_Window *window = NULL; /*On créé une variable qui pointe vers une fenetre*/
    window=(SDL_CreateWindow("Ma fenetre",SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED ,1280,720,SDL_WINDOW_SHOWN));
    
    /*Si la fenetre est nulle on recupere l'erreur et on la print*/
    if(NULL == window){
        fprintf(stderr,"Erreur SDL_CreateWindow : %s\n",SDL_GetError());
        goto Quit;
    }

    /*Creation d'une 2EME fenetre*/
    SDL_Window *window2 = NULL; /*On créé une variable qui pointe vers une fenetre*/
    window2=(SDL_CreateWindow("Ma fenetre",SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED ,200,1000,SDL_WINDOW_SHOWN));
    
    /*Si la fenetre est nulle on recupere l'erreur et on la print*/
    if(NULL == window){
        fprintf(stderr,"Erreur SDL_CreateWindow : %s\n",SDL_GetError());
        goto Quit;
    }

    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_DestroyWindow(window2);
    
Quit:
    SDL_Quit();
    return EXIT_SUCCESS;
}