/*
    GNU/Linux et MacOS
        > gcc main.c $(sdl2-config --cflags --libs) -o prog
        > gcc *.c $(sdl2-config --cflags --libs) -o prog
    Windows
        > gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
        > gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

void SDL_ExitWithError(const char *message);

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer* renderer =NULL;

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    //Création fenêtre
    window = SDL_CreateWindow("Fenetre Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if(window == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    /*------------------------------------------------------------*/
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE); //cree le rendu

    if (renderer==NULL){
        SDL_ExitWithError("Creation rendu failed");
    }

    if(SDL_SetRenderDrawColor(renderer,255,255,65,SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Erreur lors du changement de la couleur");
    }

    if(SDL_RenderDrawPoint(renderer,400,300)!=0){
        SDL_ExitWithError("Erreur lors du dessin du point");
    }
    if(SDL_RenderDrawLine(renderer,0,0,500,500)!=0){
        SDL_ExitWithError("Erreur lors du dessin de la ligne");
    }
    SDL_Rect rectangle;
    rectangle.x = 100 ;
    rectangle.y = 500;
    rectangle.w = 200 ;
    rectangle.h =  50;
    if(SDL_SetRenderDrawColor(renderer,255,1,30,SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Erreur lors du changement de la couleur");
    }

    if(SDL_RenderFillRect(renderer,&rectangle)!=0){
        SDL_ExitWithError("Erreur lors du dessin du rectangle");
    }

    SDL_RenderPresent(renderer); //affiche le rendu
    SDL_RenderClear(renderer);   //nettoye le rendu
    SDL_Delay(3000);
    /*------------------------------------------------------------*/

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}