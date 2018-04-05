#include "SDL.hpp"
#include <cstdlib>
#include <cstdio>
#include <string>

void initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Error: %s\n", SDL_GetError());
        exit(1);
	}

	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("IMG_Error: %s %s\n", IMG_GetError(), SDL_GetError());
	}
}

SDL_Surface *loadImage(std::string path, SDL_Surface *screen) {

    // Try to load the image.
    SDL_Surface *image = IMG_Load(path.data());
	if (!image) {
        printf("IMG_Error: %s\n", IMG_GetError());
        exit(1);
    }

    // SDL won't scale images as desired, if we don't match the BPP's.
	if (image->format->BitsPerPixel != screen->format->BitsPerPixel) {
        SDL_Surface *newimage = SDL_CreateRGBSurface(
            screen->flags, image->w, image->h,
            screen->format->BitsPerPixel,
            screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

        if (!newimage) {
            printf("couldn't create new rgb surface to fix the image's bpp. %s\n", SDL_GetError());
            exit(1);
        }

        if (SDL_BlitSurface(image, NULL, newimage, NULL) != 0) {
            printf("couldn't reblit the image to fix bpp. %s\n", SDL_GetError());
            exit(1);
        }

        SDL_FreeSurface(image);
        return newimage;
	} else {
        return image;
	}
}
