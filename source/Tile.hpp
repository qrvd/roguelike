#ifndef _TILE_HPP_
#define _TILE_HPP_

struct Item;
struct Monster;

struct Tile {
	enum Type { VOID, AIR, WALL, DOOR, TRAP, BUSH };
	Type type;

	Tile(Type t = VOID): type(t) {}
};

#endif