#include <stdio.h>
#include "../include/lin/SDL.h"
#include "../include/lin/SDL_ttf.h"
#include "../include/lin/SDL_image.h"
#include "time.h"
#include "CEV_gif.h"
#include <stdlib.h>
#include <stdint.h>

int main ( int argc, char* argv[] )
{
    SDL_Window* window      = NULL;
	SDL_Texture* actTexture = NULL;
	SDL_Rect blitPos 		= {0, 0 , 50 ,50};

	CEV_GifAnim * animation = NULL;

	SDL_Renderer* myRender =NULL;

    srand(time(NULL));

	if( SDL_Init( SDL_INIT_VIDEO ) <0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
	    window = SDL_CreateWindow( "SDL2 gif stress", 50, 50, 500, 500, 0);
		if( !window )
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());

		else
		{
            myRender=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(myRender,100,100,100,255);
			SDL_RenderSetLogicalSize(myRender,86,71);
			SDL_RenderClear(myRender);

            animation = CEV_gifAnimLoad("res/sprite/Florisar.gif", myRender);
            CEV_gifTimeSet(animation, GIF_ALL,500);

			actTexture = CEV_gifTexture(animation);
			CEV_gifLoopMode(animation, GIF_REPEAT_FOR);


      int quit = 0;

            //while(!interrupt())
						while(!quit)
            {
              //CEV_gifTimeSet(animation, GIF_ALL,500);

              SDL_Event event;
              while(SDL_PollEvent(&event))
              {
                switch (event.type) {
                  case SDL_QUIT:
                    quit = 1;
                    break;
                }
              }

              if(CEV_gifAnimAuto(animation))
		          {
                CEV_gifAnimAuto(animation);
                SDL_RenderClear(myRender);
                SDL_RenderCopy(myRender,actTexture,NULL,&blitPos);
                SDL_RenderPresent(myRender);
              }

            }

			CEV_gifAnimFree(animation);

		}
	}

    SDL_DestroyRenderer(myRender);
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
