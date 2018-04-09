#include "Common.hpp"
#include "Item.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Monster.hpp"
#include "Level.hpp"
#include <cstdio>
#include "SDL.hpp"

void clamp(int& num, int lower, int upper) {
    if (num < lower) num = lower;
    if (num > upper) num = upper;
}

struct Player {
	Monster avatar;
};

void draw(SDL_Surface *src, Rectangle clip, SDL_Surface* dest, Rectangle pos) {
    SDL_Rect srcrect = {clip.x, clip.y, clip.w, clip.h};
    SDL_Rect dstrect = {pos.x, pos.y, pos.w, pos.h};
    if (SDL_BlitScaled(src, &srcrect, dest, &dstrect) != 0) {
        printf("SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}

int main(int argc, char **argv) {
	Level test(80, 45);
	test.generate();
	Monster *goblin = new Monster(&test, "goblin", 20, Vector(5, 5));
	goblin->items.push_back(new Item(Item::WEAPON, Vector(0,0)));
	test.monsters.push_back(goblin);

	Vector tilesize(16, 16);
	int scale = 1;
	Vector scaledtilesize = tilesize * scale;
	Rectangle viewport(Vector(0, 0), mult(test.size, scaledtilesize));

	// Some boring SDL stuff...
	initialize();
	SDL_Window *window = SDL_CreateWindow(
        "Rogue",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        viewport.w,
        viewport.h, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Surface *screen = SDL_GetWindowSurface(window);

	Map<String, SDL_Surface*> assets;
	#include "AssetLoader.hpp"

	bool running = true;
	double accumulator = 0.0;
	double fps = 60.0;
	double fpsPerTick = 1000.0 / fps;
	double lastTime = SDL_GetTicks();

	while (running) {
	    double now = SDL_GetTicks();
        accumulator += (now - lastTime) / fpsPerTick;
        lastTime = now;
        bool shouldDraw = false;

        while (accumulator >= 1.0) {
            accumulator -= 1.0;
            shouldDraw = true;

            // Handle events
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;

                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: running = false; break;
                        case SDLK_w: goblin->pos.y--; break;
                        case SDLK_s: goblin->pos.y++; break;
                        case SDLK_a: goblin->pos.x--; break;
                        case SDLK_d: goblin->pos.x++; break;
                    }
                }
            }
        }

        if (shouldDraw) {
            // Set the viewport
            int scaledGx = goblin->pos.x * scaledtilesize.x;
            int scaledGy = goblin->pos.y * scaledtilesize.y;
            int newx = (scaledGx + scaledtilesize.x / 2) - viewport.w/2;
            int newy = (scaledGy + scaledtilesize.y / 2) - viewport.h/2;
            viewport = Rectangle(newx, newy, viewport.w, viewport.h);

            clamp(viewport.x, 0, test.size.x * scaledtilesize.x - viewport.w);
            clamp(viewport.y, 0, test.size.y * scaledtilesize.x - viewport.h);

            Vector offset(viewport.x, viewport.y);

            // Clear
            SDL_FillRect(screen, NULL, 0);

            // Draw tiles
            for (int y = 0; y < test.size.y; y++) {
                for (int x = 0; x < test.size.x; x++) {
                    Rectangle posRect(mult(Vector(x, y), scaledtilesize) - offset, scaledtilesize);
                    Tile t = *test.getTile(x, y);

                    Vector clip(0, 0);
                    String assetName = "Tile";

                    // Determine the position of tile to use, and the asset file to use.
                    switch (t.type) {
                        case Tile::VOID: clip = Vector(0, 2); break;
                        case Tile::AIR:  clip = Vector(0, 0); break;
                        case Tile::WALL: clip = Vector(3, 2); break;
                        case Tile::DOOR: clip = Vector(0, 3); break;
                        case Tile::TRAP: clip = Vector(2, 3); assetName = "Trap1"; break;
                        case Tile::BUSH: clip = Vector(4, 0); break;
                    }

                    // Scale according to the actual tile size
                    draw(assets[assetName], Rectangle(mult(clip, tilesize), tilesize), screen, posRect);
                }
            }

            // Draw items
            for (Item *i: test.items.entries) {
                Rectangle posRect = Rectangle(mult(i->pos, scaledtilesize), scaledtilesize);
                switch (i->type) {
                    case Item::POTION:
                        draw(assets["Potion"], Rectangle(tilesize), screen, posRect);
                        break;
                    case Item::SCROLL:
                        draw(assets["Scroll"], Rectangle(tilesize), screen, posRect);
                        break;
                    case Item::WEAPON:
                        draw(assets["MedWep"], Rectangle(tilesize), screen, posRect);
                        break;
                }
            }

            // Draw monsters
            for (Monster *m: test.monsters.entries) {
                Rectangle posRect = Rectangle(mult(m->pos, scaledtilesize) - offset, scaledtilesize);
                draw(assets["Aquatic0"], Rectangle(Vector(), tilesize), screen, posRect);
            }

            SDL_UpdateWindowSurface(window);
        }
	}

	return 0;
}
