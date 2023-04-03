#ifndef COMMUN_H
#define COMMUN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void drawCases(SDL_Renderer *renderer, int x, int y, int width, int height, int rows, int cols);

#endif