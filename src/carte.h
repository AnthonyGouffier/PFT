#ifndef CARTE_H
#define CARTE_H

#include <SDL.h>


typedef struct {
    bool click;
    SDL_Rect lvlRect;
    SDL_Rect blackRect;
    SDL_Rect blueRect;
    SDL_Rect destRect ;
    SDL_Rect prixRect;
    SDL_Rect nomRect; 
    SDL_Rect rectanglePiece;
    SDL_Texture* bgTexture;
    SDL_Texture* pkmTexture;
    SDL_Texture* pieceTexture;
    SDL_Texture* textureText;
    SDL_Texture* prixTexture;
    SDL_Texture* nomTexture;
}carteBoutique;

carteBoutique genererCartePkmBoutique(pokemon_t ,SDL_Renderer* , SDL_Window *  ,int  , int , int , int) ;
void afficherCartePkmBoutique(carteBoutique ,SDL_Renderer* ,pokemon_t );

#endif