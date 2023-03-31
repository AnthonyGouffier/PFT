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
  SDL_Texture* actTexture_back = NULL;

  SDL_Texture* actTexture_g = NULL;
  SDL_Texture* actTexture_g_back = NULL;
	SDL_Rect blitPos 		= {0, 0 , 50 ,50};
  SDL_Rect blitPos2 		= {0, 0 , 50 ,50};
  SDL_Rect blitPos3 		= {0, 0 , 50 ,50};
  SDL_Rect blitPos4 		= {0, 0 , 50 ,50};

	CEV_GifAnim * animation = NULL;
  CEV_GifAnim * animation_back = NULL;

  CEV_GifAnim * animation_g = NULL;
  CEV_GifAnim * animation_g_back = NULL;


	SDL_Renderer* myRender =NULL;

    srand(time(NULL));

	if( SDL_Init( SDL_INIT_VIDEO ) <0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
	    window = SDL_CreateWindow( "SDL2 gif stress", 50, 50, 750, 500, 0);
		if( !window )
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());

		else
		{
      myRender=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
      SDL_SetRenderDrawColor(myRender,154,188,245,255);
			SDL_RenderSetLogicalSize(myRender,125,100);
			SDL_RenderClear(myRender);

      animation = CEV_gifAnimLoad("res/sprite/charizard.gif", myRender);

      animation_back = CEV_gifAnimLoad("res/sprite/charizard_back.gif", myRender);


      animation_g = CEV_gifAnimLoad("res/sprite/G.gif", myRender);

      animation_g_back = CEV_gifAnimLoad("res/sprite/G_back.gif", myRender);

			actTexture = CEV_gifTexture(animation);
			CEV_gifLoopMode(animation, GIF_REPEAT_FOR);

      actTexture_back = CEV_gifTexture(animation_back);
      CEV_gifLoopMode(animation_back, GIF_REPEAT_FOR);

      actTexture_g = CEV_gifTexture(animation_g);
      CEV_gifLoopMode(animation_g, GIF_REPEAT_FOR);

      actTexture_g_back = CEV_gifTexture(animation_g_back);
      CEV_gifLoopMode(animation_g_back, GIF_REPEAT_FOR);


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
                blitPos.x = 40;
                blitPos.w = 50;
                blitPos.h = 50;

                CEV_gifAnimAuto(animation);
                SDL_RenderCopy(myRender,actTexture,NULL,&blitPos);

                blitPos2.x=0;
                blitPos2.w = 50;
                blitPos2.h = 50;

                CEV_gifAnimAuto(animation_back);
                SDL_RenderCopy(myRender,actTexture_back,NULL,&blitPos2);

                blitPos3.y = 50;
                blitPos3.x = 0;
                blitPos3.w = 79;
                blitPos3.h = 50;

                CEV_gifAnimAuto(animation_g);
                SDL_RenderCopy(myRender,actTexture_g,NULL,&blitPos3);

                blitPos4.y = 50;
                blitPos4.x = 50;
                blitPos4.w = 79;
                blitPos4.h = 50;

                CEV_gifAnimAuto(animation_g_back);
                SDL_RenderCopy(myRender,actTexture_g_back,NULL,&blitPos4);


                SDL_RenderPresent(myRender);
                //usleep(1000000);
                SDL_RenderClear(myRender);



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
