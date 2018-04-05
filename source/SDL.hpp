#ifndef _SDL_HPP_
#define _SDL_HPP_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#undef main
#include <string>

void initialize();
SDL_Surface *loadImage(std::string path, SDL_Surface *screen);

#endif
