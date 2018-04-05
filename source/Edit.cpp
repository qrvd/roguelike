#include "Common.hpp"
#include "Item.hpp"
#include "Monster.hpp"
#include "Tile.hpp"
#include "Monster.hpp"
#include "Level.hpp"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#undef main

int main(int argc, char **argv) {
    Level test(Vector(40, 40));
    Level::Tree root(Rectangle(Vector(0, 0), test.size));

    return 0;
}
