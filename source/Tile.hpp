#ifndef _TILE_HPP_
#define _TILE_HPP_

struct Item;
struct Monster;

struct Tile {
	enum Type { VOID, AIR, WALL, DOOR, TRAP, BUSH };
	Type type;

	bool passable;
	bool solid;

	Tile(Type t = VOID): type(t), passable(true), solid(false) {}
};

#endif
